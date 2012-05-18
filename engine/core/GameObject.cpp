//
//  GameObject.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameObject.h"
#include <algorithm>
#include "RenderPipeline.h"

//******************************************************************************
// Construct/destruct

GameObject::GameObject(const std::string& name) {
	
	_name = name;
	_transform = AddComponent<class Transform>();
	_renderer = 0;
	_inHierarchy = false;
	_rigidbody = 0;
	_active = true;
}

//------------------------------------------------------------------------------

GameObject::~GameObject() {
	
}

//******************************************************************************
// General parameters

void GameObject::SetMaterial(Material material, bool recursively) {
    
	if (Renderer()) {
		Renderer()->Material(material);
	}
	
	if (recursively) {
		for (TransformList::const_iterator it = Transform()->Children().begin(); it != Transform()->Children().end(); it++) {
			(*it)->GameObject()->SetMaterial(material, recursively);
		}
	}
}

//------------------------------------------------------------------------------

void GameObject::SetActiveRecursively(bool active) {
    
	_active = active;
    
	for (TransformList::const_iterator it = Transform()->Children().begin(); it != Transform()->Children().end(); it++) {
		(*it)->GameObject()->SetActiveRecursively(active);
	}
}

//******************************************************************************
// Component methods

MeshRenderer *GameObject::Renderer() const {
	
	if (!_renderer) {
		_renderer = this->GetComponent<MeshRenderer>();
	}
	
	return _renderer;
}

//------------------------------------------------------------------------------

#ifdef ENABLE_PHYSICS
class Rigidbody *GameObject::Rigidbody() {
	
	if (!_rigidbody) {
		_rigidbody = this->GetComponent<class Rigidbody>();
	}
	
	return _rigidbody;
}
#endif

//******************************************************************************
// Event



//******************************************************************************
// Search

GameObject *GameObject::SearchGameObject(const std::string &objectName) {
    
    return _objectSearch->SearchGameObject(objectName);
}


//******************************************************************************
// Update methods

void GameObject::PreStart() {
	
	for (ComponentList::iterator it = _components.begin(); it != _components.end(); it++) {
		if (it->get()->Active()) {
			it->get()->PreStart();
		}
	}
}


void GameObject::Start() {
	
	for (ComponentList::iterator it = _components.begin(); it != _components.end(); it++) {
		if (it->get()->Active()) {
			it->get()->Start();
		}
	}
}


void ProcessPreUpdate(const ComponentPtr& component) {
    
	if (component->Active()) {
		component->PreUpdate();
	}
}

void GameObject::PreUpdate() {
	
	std::for_each(_components.begin(), _components.end(), ProcessPreUpdate);
}


void GameObject::Update() {
    
	for (ComponentList::iterator it = _components.begin(); it != _components.end(); it++) {
		if (it->get()->Active()) {
			it->get()->Update();
		}
	}
}


void GameObject::Render() {
	
	for (ComponentList::iterator it = _components.begin(); it != _components.end(); it++) {
		if (it->get()->Active()) {
			it->get()->Render();
		}
	}
}

void ProcessPreRender(const ComponentPtr& component) {
	
	if (component->Active()) {
		component->PreRender();
	}
}


void GameObject::PreRender() {
	
	std::for_each(_components.begin(), _components.end(), ProcessPreRender);	
}


void GameObject::PhysicsTick() {
	
	for (ComponentList::iterator it = _components.begin(); it != _components.end(); it++) {
		if (it->get()->Active()) {
			it->get()->PhysicsTick();
		}
	}
}


void GameObject::SendStart(const ComponentPtr& component) {
    
	if (component->Active()) {
		component->Start();
	}
}