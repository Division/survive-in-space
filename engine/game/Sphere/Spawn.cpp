//
//  Spawn.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Spawn.h"
#include "Transform.h"

//******************************************************************************
//
//  Public
//
//******************************************************************************


//******************************************************************************
// Construct/destruct

Spawn::Spawn() {
	
	_angle = 0;
}


Spawn::~Spawn() {

	
}

//******************************************************************************
// Component

void Spawn::Update() {
	
	_angle += M_PI / 4 * utils::DeltaTime();
//	Transform()->Position(position + normal * (float)abs(sin(_angle) * 100));
	
	Transform()->Rotation(math::Rotate(q, _angle * RAD2DEG, Vector3(0,1,0)));
	
/*	_angle += 45 * utils::DeltaTime();
	Quaternion q = math::Rotation(_angle, Vector3(0,1,0));
	Transform()->Rotation(q);*/
}