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

#include "ComponentDeclaration.h"

typedef std::unique_ptr<Component> ComponentPtr;
typedef std::vector<ComponentPtr> ComponentList;
class RenderPipeline;

class GameObject : public ObjectSearch {
public:
	GameObject(const std::string& name = "GameObject");
	~GameObject();
	
	Transform *Transform() const { return _transform; }
	MeshRenderer *Renderer() const;
	
    virtual GameObject *SearchGameObject(const std::string &objectName);
    class ObjectSearch *ObjectSearch() const { return _objectSearch; };
    void ObjectSearch(class ObjectSearch *search) { _objectSearch = search; }
    
	#ifdef ENABLE_PHYSICS
	class Rigidbody *Rigidbody();
	#endif
	
	std::string Name(void) const { return _name; }
	void Name(std::string name) { _name = name; }
	
	template <class T>
	T* GetComponent() const;

	template <class T>
	T* AddComponent();
	
	void SetMaterial(Material material, bool recursively = false);
		
	void Active(bool active) { _active = active; }
	bool Active() { return _active; }
	
	class RenderPipeline *RenderPipeline() { return _renderPipeline; }
	void RenderPipeline(class RenderPipeline *pipeline) { _renderPipeline = pipeline; }
	
	// todo make it all protected
	void PreStart();
	void Start(); 
	void PreUpdate();
	void Update(); 
	void PreRender();
	void Render(); 
	void PhysicsTick();
	void InHierarchy(bool inHierarchy);
	bool InHierarchy() const { return _inHierarchy; }
	void SetActiveRecursively(bool active);
	
private:
	static void SendStart(const ComponentPtr& component);
	
private:
	
    class ObjectSearch *_objectSearch;
    
	#ifdef ENABLE_PHYSICS
	class Rigidbody *_rigidbody;
	#endif
	
	mutable ComponentList _components;
	std::string _name;
	class Transform *_transform;
	mutable MeshRenderer *_renderer;
	bool _inHierarchy;
	bool _active;
	class RenderPipeline *_renderPipeline;
};


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
