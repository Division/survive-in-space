//
//  PlayerController.cpp
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PlayerController.h"
#include "Utils.h"
#include "GameObject.h"
#include "PlayerShip.h"

static const float STICKER_RADIUS = 20;


void PlayerController::Start() {

	_player = GameObject()->GetComponent<PlayerShip>();
}


void PlayerController::PreUpdate() {

	ProcessDeviceInput();

	// Simulator makes additional input
	if (!utils::IsRunningDevice()) {
		ProcessSimulatorInput();
	}
}


void PlayerController::ProcessDeviceInput() {
	
	input::Touch *touch;
	bool stickerProcessed = false;
	
	for (int i = 0; i < input::TouchCount(); i++) {
		
		touch = input::GetTouch(i);
		
		if (!stickerProcessed && IsStickerPart(touch->position)) {
			ProcessStickerTouch(touch);
			stickerProcessed = true;
		}
		
		if (IsButtonPart(touch->position)) {
			ProcessButtonTouch(touch);
		}
	}
	
	if (!stickerProcessed) {
		SetStickerValue(Vector3(0));
		_stickerEnabled = false;
	}
	
	_acceleration = 1;
	
	_player->SetControlsValues(_normalizedStickerValue, 0, _acceleration);
}


void PlayerController::ProcessSimulatorInput() {


}


void PlayerController::ProcessStickerTouch(input::Touch *touch) {

	Vector3 stickerDelta;
	
	switch (touch->phase) {
		case input::TouchPhaseBegan:
			
			_stickerEnabled = true;
			_initialStickerPos = touch->position;
			break;
			
		case input::TouchPhaseMoved:
			
			if (!_stickerEnabled) {
				_initialStickerPos = touch->position;
				_stickerEnabled = true;
			}
			
			stickerDelta = touch->position - _initialStickerPos;
			SetStickerValue(stickerDelta);
			break;
			
		case input::TouchPhaseEnd:
			
			_stickerEnabled = false;
			SetStickerValue(Vector3(0));
			break;
			
		default:
			
			break;
	}
}


void PlayerController::ProcessButtonTouch(input::Touch *touch) {
	
	
}


void PlayerController::SetStickerValue(const Vector3 &value) {
	
	_normalizedStickerValue = value / StickerRadius();
	if (_normalizedStickerValue.length() > StickerRadius()) {
		_normalizedStickerValue = math::Normalize(_normalizedStickerValue) * StickerRadius();
	}
}


bool PlayerController::IsButtonPart(const Vector3 &pos) {
	
	return pos.x > 300;
}


bool PlayerController::IsStickerPart(const Vector3 &pos) {

	return pos.x < 200;
}


float PlayerController::StickerRadius() {

	return STICKER_RADIUS;
}