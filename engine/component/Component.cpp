//
//  BaseComponent.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Event.h"

//******************************************************************************
// Construct/destruct

Component::Component() {

}

//------------------------------------------------------------------------------

Component::~Component() {
	
}

//******************************************************************************
// Properties

void Component::GameObject(class GameObject *gameObject) {
	
	_gameObject = gameObject;	
}

//------------------------------------------------------------------------------

class Transform *Component::Transform() {
	
	return _gameObject->Transform();
}

//******************************************************************************
// Event

void Component::RegisterEvent(int eventID) {
	
	GameObject()->RegisterEvent(eventID, this);
}

//------------------------------------------------------------------------------

void Component::RemoveEvent(int eventID) {

	GameObject()->RemoveEvent(eventID, this);
}

//------------------------------------------------------------------------------

void Component::ProcessEvent(Event *event) {
	
}

//------------------------------------------------------------------------------

bool Component::DispatchEvent(Event *event, int dispatchType) {
	
	return GameObject()->DispatchEvent(event, (EventDispatchType)dispatchType);
}

//******************************************************************************
// Update methods

void Component::PreUpdate() {
	
}

//------------------------------------------------------------------------------

void Component::Update() {

}

//------------------------------------------------------------------------------

void Component::Awake() {
	
}

//------------------------------------------------------------------------------

void Component::PreStart() {
	
}

//------------------------------------------------------------------------------

void Component::Start() {
	
}

//------------------------------------------------------------------------------

void Component::PreRender() {
	
}

//------------------------------------------------------------------------------

void Component::Render() {
	
}

//------------------------------------------------------------------------------

void Component::PhysicsTick() {
	
}
