//
//  GameObject.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>
#include <string>
#include "Physics.h"
#include "ObjectSearch.h"
#include "Event.h"

#include "ComponentDeclaration.h"

typedef std::unique_ptr<Component> ComponentPtr;
typedef std::vector<ComponentPtr> ComponentList;
class RenderPipeline;

typedef enum {
	EventDispatchComponents,
	EventDispatchBroadcast,
	EventDispatchGlobalBroadcast,
	EventDispatchUpwards
} EventDispatchType;


class GameObject : public ObjectSearch {
public:

    //--------------------------
    // Construct/destruct
	GameObject(const std::string& name = "GameObject");
	~GameObject();

    //--------------------------
    // General parameters
	std::string Name(void) const { return _name; }
	void Name(std::string name) { _name = name; }

	void InHierarchy(bool inHierarchy) { _inHierarchy = inHierarchy; };
	bool InHierarchy() const { return _inHierarchy; }

	void SetMaterial(Material material, bool recursively = false);
    
	void Active(bool active) { _active = active; }
	bool Active() { return _active; }
	void SetActiveRecursively(bool active);
    
	class RenderPipeline *RenderPipeline() { return _renderPipeline; }
	void RenderPipeline(class RenderPipeline *pipeline) { _renderPipeline = pipeline; }
    
    //--------------------------
    // Component methods
	template <class T>
	T* GetComponent() const;
    
	template <class T>
	T* AddComponent();
    
	Transform *Transform() const { return _transform; }
	MeshRenderer *Renderer() const;
    
    #ifdef ENABLE_PHYSICS
	class Rigidbody *Rigidbody();
    #endif
	
    //--------------------------
    // Event
    void RegisterEvent(int eventID, Component *component);
    void RemoveEvent(int eventID, Component *component);
    bool DispatchEvent(Event *event, EventDispatchType dispatchType = EventDispatchComponents);
	void GlobalDispatcher(EventDispatcher *dispatcher) { _globalDispatcher = dispatcher; }
	EventDispatcher *GlobalDispatcher() const { return _globalDispatcher; }
	
    //--------------------------
    // Search
    virtual GameObject *SearchGameObject(const std::string &objectName);
    class ObjectSearch *ObjectSearch() const { return _objectSearch; };
    void ObjectSearch(class ObjectSearch *search) { _objectSearch = search; }
    
	//--------------------------
    // Update methods
	void PreStart();
	void Start(); 
	void PreUpdate();
	void Update(); 
	void PreRender();
	void Render(); 
	void PhysicsTick();
	
private:
	static void SendStart(const ComponentPtr& component);
	
private:

    //--------------------------
    // Properties
	bool _inHierarchy;
	bool _active;
	std::string _name;
    
    //--------------------------
    // Components
	#ifdef ENABLE_PHYSICS
	class Rigidbody *_rigidbody;
	#endif
	class Transform *_transform;
	mutable MeshRenderer *_renderer;
    
	mutable ComponentList _components;

    //--------------------------
    // Helper objects
	class RenderPipeline *_renderPipeline;
    class ObjectSearch *_objectSearch;
    EventDispatcher _eventDispatcher;
	EventDispatcher *_globalDispatcher;
};

//******************************************************************************
//
//  Template methods
//
//******************************************************************************

template <class T>
T* GameObject::AddComponent() {
	
	T* component = new T();
	component->GameObject(this);
	component->Active(true);
	component->Awake();
	
	ComponentPtr componentPtr(component);

	if (_inHierarchy) {
		SendStart(componentPtr);
	}

	_components.push_back(std::move(componentPtr));
	
	return component;
}

//------------------------------------------------------------------------------

class ComponentFinder {
public:
	ComponentFinder(int id) { _id = id; }
	
	bool operator()(const ComponentPtr& item) {
		int itemID = item->GetID();
		return  itemID == _id;
	}
	
private:
	int _id;
	
};

//------------------------------------------------------------------------------

template <class T>
T* GameObject::GetComponent() const {
	
	T* result = NULL;
	
	// Init finder with ID() property of T type
	int searchID = T::ID();
	ComponentFinder finder(searchID);
	ComponentList::iterator it = std::find_if(_components.begin(), _components.end(), finder);
	
	if (it != _components.end()) {
		result = (T*) it->get();
	}
	
	return result;
}


#endif
