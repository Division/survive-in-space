//
//  PlayerShip.h
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "Component.h"
#include "MyMath.h"

class Rigidbody;

class PlayerShip : public Component {
public:
	GENERATE_COMPONENT_ID(PlayerShip)
	
	virtual void Start();
	virtual void Update();
	virtual void PhysicsTick();
	virtual void ProcessEvent(Event *event);
	
private:
	void ProcessPhysicsControls();
	void SetControlsValues(const Vector3 &sticker, float roll, float acceleration);
	
private:
	Vector3 _stickerControl;
	float _rollControl;
	float _accelerationControl;
    float _currentSpeed;
};


#endif
