//
//  TouchPlayerController.cpp
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "TouchPlayerController.h"
#include "Utils.h"
#include "GameObject.h"
#include "TouchPlayerControllerEvent.h"
#include "TouchGameUIEvent.h"

static const float STICKER_RADIUS = 60;

//******************************************************************************
//
//  Public
//
//******************************************************************************

float TouchPlayerController::StickerRadius() const {
    
	return STICKER_RADIUS;
}

//******************************************************************************
// Component

void TouchPlayerController::Start() {

    _touchID = -1;
	RegisterEvent<TouchPlayerControllerGetDataEvent>();
	RegisterEvent<TouchGameUIButtonEvent>();
}

//------------------------------------------------------------------------------


void TouchPlayerController::PreUpdate() {

	ProcessDeviceInput();
}

//******************************************************************************
// Event

void TouchPlayerController::ProcessEvent(Event *event) {
	
	// Put current control data into event
	TouchPlayerControllerGetDataEvent *getDataEvent;
	if (TouchPlayerControllerGetDataEvent::Match(event, &getDataEvent)) {
		getDataEvent->stickerEnabled = _stickerEnabled;
		getDataEvent->stickerRadius = StickerRadius();
		getDataEvent->initialStickerPos = InitialStickerPos();
		getDataEvent->currentStickerPos = CurrentStickerPos();
		return;
	}
	
	// Speed buttons state
	TouchGameUIButtonEvent *buttonEvent;
	if (TouchGameUIButtonEvent::Match(event, &buttonEvent)) {
		SetSpeedButtonsState(buttonEvent->speedUp, buttonEvent->speedDown);
		return;
	}	
}

//******************************************************************************
// Controls

// Called from GameUI
void TouchPlayerController::SetSpeedButtonsState(bool speedUpEnabled, bool speedDownEnabled) {
    
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

void TouchPlayerController::ProcessDeviceInput() {
	
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
	
	TouchPlayerControllerEvent event;
	event.sticker = _normalizedStickerValue;
	event.acceleration = _speedControlValue;
	event.roll = GetRollFactor();
	
	// Received in PlayerShip
	DispatchEvent(&event);
}

//------------------------------------------------------------------------------

void TouchPlayerController::SetStickerValue(const Vector3 &value) {
	
	_normalizedStickerValue = value / StickerRadius();
    
	if (math::Length(_normalizedStickerValue) > 1.0f) {
		_normalizedStickerValue = math::Normalize(_normalizedStickerValue);
	}
    
    _stickerValue = _normalizedStickerValue * StickerRadius();
}

//------------------------------------------------------------------------------

void TouchPlayerController::ProcessStickerTouch(input::Touch *touch) {

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

float TouchPlayerController::GetRollFactor() {
	
	float factor = 0;
	
	Vector3 acc;
	if (input::GetAccelerometerData(acc)) {
		
		float minValue = 0.15;
		float multKoef = 4;
		float maxValue = 1;
		
		float power = math::abs(acc.y);
		if (power > minValue) {
			power = power - minValue;
			power *= multKoef;
			if (power > maxValue) power = maxValue;
			
			bool inverse = (acc.y < 0) ^ (acc.x < 0);
			if (inverse) power *= -1;

			factor = power;
		}
	}
	
	return factor;
}

//******************************************************************************
// Utils

bool TouchPlayerController::IsButtonPart(const Vector3 &pos) {
	
	return pos.x > 300;
}

//------------------------------------------------------------------------------

bool TouchPlayerController::IsStickerPart(const Vector3 &pos) {

    Vector2 resolution = utils::GetInputResolution();
	return pos.x < resolution.x / 2.0f;
}
