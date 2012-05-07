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
#import "Transform.h"

Component::Component() {

}

void Component::GameObject(class GameObject *gameObject) {
	_gameObject = gameObject;	
}

Component::~Component() {
	
}

class Transform *Component::Transform() {
	
	return _gameObject->Transform();
}

void Component::PreUpdate() {
	
}

void Component::Update() {

}

void Component::Awake() {
	
}

void Component::PreStart() {
	
}

void Component::Start() {
	
}

void Component::PreRender() {

}

void Component::PhysicsTick() {
	
}