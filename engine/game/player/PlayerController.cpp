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
#include "PlayerControllerEvent.h"

static const float STICKER_RADIUS = 60;

//******************************************************************************
//
//  Public
//
//******************************************************************************

float PlayerController::StickerRadius() const {
    
	return STICKER_RADIUS;
}

//******************************************************************************
// Component

void PlayerController::Start() {

	_player = GameObject()->GetComponent<PlayerShip>();
    _touchID = -1;
}

//------------------------------------------------------------------------------

void PlayerController::PreUpdate() {

	ProcessDeviceInput();
}

//******************************************************************************
// Controls

// Called from GameUI
void PlayerController::SetSpeedButtonsState(bool speedUpEnabled, bool speedDownEnabled) {
    
    if (speedUpEnabled) {
        _speedControlValue = 1;
    } else if (speedDownEnabled) {
        _speedControlValue = -1;
    } else {
        _speedControlValue = 0;
    }
}

//******************************************************************************
//
//  Private
//
//******************************************************************************

//******************************************************************************
// Control values calculation

void PlayerController::ProcessDeviceInput() {
	
	input::Touch *touch;
	bool stickerProcessed = false;
    
	bool isTrackingTouch = _touchID != -1;
	
    for (int messageID = 0; messageID < input::TouchMessageCount(); messageID++) {
		
        for (int i = 0; i < input::TouchCount(messageID); i++) {
            
            touch = input::GetTouch(messageID, i);
            
            if (isTrackingTouch) {
                // Touch is currently down
                if (touch->id != _touchID) continue;
                
                if (touch->phase != input::TouchPhaseEnd) {
                    // Touch live
                    ProcessStickerTouch(touch);
                    stickerProcessed = true;
                } else {
                    // Touch dead
                    _touchID = -1;
					isTrackingTouch = false;
                }
            } else {
                // No touches at the moment
                if (touch->phase == input::TouchPhaseBegan && IsStickerPart(touch->position)) {
                    _touchID = touch->id;
                    stickerProcessed = true;
                    ProcessStickerTouch(touch);
                }
            }
        }
    }
	
	if (!stickerProcessed) {
		SetStickerValue(Vector3(0));
		_stickerEnabled = false;
	}
	
	_player->SetControlsValues(_normalizedStickerValue, 0, _speedControlValue);
	
	utils::Log("send");
	PlayerControllerEvent event;
	event.message = "Hello!";
	DispatchEvent(&event);
}

//------------------------------------------------------------------------------

void PlayerController::SetStickerValue(const Vector3 &value) {
	
	_normalizedStickerValue = value / StickerRadius();
    
	if (math::Length(_normalizedStickerValue) > 1.0f) {
		_normalizedStickerValue = math::Normalize(_normalizedStickerValue);
	}
    
    _stickerValue = _normalizedStickerValue * StickerRadius();
}

//------------------------------------------------------------------------------

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

//******************************************************************************
// Utils

bool PlayerController::IsButtonPart(const Vector3 &pos) {
	
	return pos.x > 300;
}

//------------------------------------------------------------------------------

bool PlayerController::IsStickerPart(const Vector3 &pos) {

    Vector2 resolution = utils::GetInputResolution();
	return pos.x < resolution.x / 2.0f;
}
