//
//  PlayerController.h
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Component.h"
#include "MyMath.h"
#include "Input.h"

class PlayerShip;

class PlayerController : public Component {
public:
	GENERATE_COMPONENT_ID(PlayerController)
	
	virtual void Start();
	virtual void PreUpdate();
	
private:
	void ProcessDeviceInput();
	void ProcessSimulatorInput();
	bool IsStickerPart(const Vector3 &pos);
	bool IsButtonPart(const Vector3 &pos);
	
	void ProcessStickerTouch(input::Touch *touch);
	void ProcessButtonTouch(input::Touch *touch);
	
	void SetStickerValue(const Vector3 &value);
	float StickerRadius();
	
private:
	PlayerShip *_player;
	Vector3 _initialStickerPos;
	bool _stickerEnabled;
	Vector3 _normalizedStickerValue;
	float _acceleration;
};

#endif
