//
//  Camera.cpp
//  Cpptest
//
//  Created by Nikita on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Camera.h"
#include "Utils.h"
#include "ComponentDeclaration.h"
#include "GameObject.h"

Camera *Camera::_mainCamera = 0;

void Camera::Awake() {

	if (!_mainCamera) {
		_mainCamera = this;
	} else {
		utils::Log("Main camera already exists");
	}
}


void Camera::Update() {
	
	Rigidbody *rigidbody =  GameObject()->Rigidbody();
	if (rigidbody) {
//		rigidbody->Body()->applyTorque(btVector3(0,1,0));
	}
}


void Camera::CalculateMatrix() {

	_projectionMatrix = math::Perspective(45.0, 960.0/640.0, 1.0, 1000.0);
	
	Matrix4 transformMatrix = Transform()->TransformToWorldMatrix();
	_worldMatrix = glm::inverse(transformMatrix);
}


void Camera::PreRender() {

	CalculateMatrix();
}