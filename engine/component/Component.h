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
	
	Component();
	~Component();
	
	class Transform *Transform();
	
	class GameObject *GameObject() const { return _gameObject; }
	void GameObject(class GameObject *gameObject);

	bool Active() const { return _active; }
	void Active(bool active) { _active = active; }
	
	virtual void Awake();
	virtual void PreStart();
	virtual void Start();
	virtual void PreUpdate();
	virtual void Update();
	virtual void PreRender(); // Called after update and before render
	virtual void PhysicsTick();
	virtual void Render();
    virtual void ProcessEvent(Event *event);
	
protected:
	class GameObject *_gameObject;
	bool _active;
	
};



#endif
