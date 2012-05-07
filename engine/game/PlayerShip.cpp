//
//  PlayerShip.cpp
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PlayerShip.h"
#include "Camera.h"
#include "ComponentDeclaration.h"
#include "MyMath.h"
#include "Rigidbody.h"
#include "GameObject.h"

void PlayerShip::Start() {

	Camera::Main()->Transform()->Parent(Transform());
	Camera::Main()->Transform()->Position(Vector3(0,4,10));
	Camera::Main()->Transform()->Rotation(math::Rotation(-15, Vector3(1,0,0)));
	
	Quaternion shipRotation = math::Rotation(90, Vector3(1,0,0));
	math::Rotate(shipRotation, 180, Vector3(0,0,1));
	
	Transform()->Find("Ship")->Rotation(shipRotation);
}


void PlayerShip::PhysicsTick() {
	
	ProcessPhysicsControls();
}


void PlayerShip::ProcessPhysicsControls() {
	
	btRigidBody *body = GameObject()->Rigidbody()->Body();
	
	if (!body) return;
	body->setActivationState(DISABLE_DEACTIVATION);
	body->setDamping(0.9, 0.95);
	
	float moveKoef = 300;
	btVector3 moveForce = btVector3(0,0,-moveKoef) * _accelerationControl;
	btVector3 torqueForce = btVector3(-_stickerControl.y, -_stickerControl.x, 0.0);
	torqueForce *= 8;

	torqueForce = body->getWorldTransform().getBasis() * torqueForce;
	
	body->applyCentralForce(body->getWorldTransform().getBasis() * moveForce);
	body->applyTorque(torqueForce);
}


void PlayerShip::SetControlsValues(const Vector3 &sticker, float roll, float acceleration) {

	_stickerControl = sticker;
	_rollControl = roll;
	_accelerationControl = acceleration;
}