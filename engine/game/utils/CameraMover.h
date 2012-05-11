//
//  CameraMover.h
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CAMERA_MOVER_H
#define CAMERA_MOVER_H

#include "Component.h"
#include "MyMath.h"

class CameraMover: public Component {
public:
	GENERATE_COMPONENT_ID(CameraMover)
	
	void Update();

private:
	void RotateCamera();
	void MoveCamera(float delta);
	
private:
	Vector3 _delta;
	
};

#endif
