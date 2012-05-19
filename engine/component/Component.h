//
//  BaseComponent.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include "Utils.h"

#define GENERATE_COMPONENT_ID(className) \
static int ID() { return utils::Hash(#className); } \
int GetID() { return \
className::ID(); \
}


class Transform;
class GameObject;
class Event;

class Component {
public:
	
	virtual int GetID() = 0;
	
	//-------------------
	// Construct/destruct
	Component();
	~Component();
	
	//-------------------
	// General properties
	class Transform *Transform();
	
	class GameObject *GameObject() const { return _gameObject; }
	void GameObject(class GameObject *gameObject);

	bool Active() const { return _active; }
	void Active(bool active) { _active = active; }
	
	//-------------------
	// Event
	
	template <class T>
	void RegisterEvent();
	void RegisterEvent(int eventID);
	template <class T>
	void RemoveEvent();
	void RemoverEvent(int eventID);

	void DispatchEvent(Event *event, int dispatchType = 0);
	
    virtual void ProcessEvent(Event *event);
	
	//-------------------
	// Update methods
	virtual void Awake();
	virtual void PreStart();
	virtual void Start();
	virtual void PreUpdate();
	virtual void Update();
	virtual void PreRender(); // Called after update and before render
	virtual void PhysicsTick();
	virtual void Render();
	
protected:
	class GameObject *_gameObject;
	bool _active;
	
};

//******************************************************************************
//
//  Template methods
//
//******************************************************************************


template <class T>
void Component::RegisterEvent() {
	
	int eventID = T::ID();
	RegisterEvent(eventID);
}

//------------------------------------------------------------------------------

template <class T>
void Component::RemoveEvent() {
	
	int eventID = T::ID();
	RemoveEvent(eventID);
}

#endif
