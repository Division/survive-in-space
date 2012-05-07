//
//  CameraMover.cpp
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CameraMover.h"
#include "Input.h"
#include "Transform.h"

static bool forward = false;

void CameraMover::Update() {

	if (input::TouchCount() == 1) {
		RotateCamera();
	} else if (input::TouchCount() > 1) {

		if (input::GetTouch(0)->phase == input::TouchPhaseBegan) {
			forward = !forward;
		}

		MoveCamera(forward ? -1 : 1);
	}
	
}


void CameraMover::RotateCamera() {
	
	input::Touch *touch = input::GetTouch(0);
	if (!touch) return;
	if (touch->phase != input::TouchPhaseMoved) return;
	
	_delta += (touch->position - touch->prevPosition) * Vector3(0.15,0.15,0.15);
	
	if (_delta.y < -89) _delta.y = -89;
	if (_delta.y > 89) _delta.y = 89;
	
	Quaternion currentRotation = Transform()->Rotation();
	
	Quaternion deltaRotation;
	deltaRotation = math::Rotate(deltaRotation, _delta.x, Vector3(0,1,0));
	deltaRotation = math::Rotate(deltaRotation, _delta.y, Vector3(1,0,0));
	
	Transform()->Rotation(deltaRotation);
}


void CameraMover::MoveCamera(float delta) {
	
	Vector3 deltaVec = -Transform()->Forward() * Vector3(delta);
	Vector3 newPos = deltaVec + Transform()->Position();
	Transform()->Position(newPos);
}
