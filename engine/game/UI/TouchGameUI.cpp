//
//  GameUI.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "TouchGameUI.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "GetData.h"
#include "Resource.h"
#include "TouchPlayerControllerEvent.h"
#include "Transform.h"
#include "TouchGameUIEvent.h"

static const int StickerBackgroundRenderQueue = RenderQueueOverlay + 10;
static const int StickerRenderQueue = StickerBackgroundRenderQueue + 1;
static const int SpeedButtonRenderQueue = StickerBackgroundRenderQueue;
static const float SpeedButtonWidth = 128;
static const float SpeedButtonHeight = 64;

//******************************************************************************
//
//  Public
//
//******************************************************************************

void TouchGameUI::Awake() {

    _speedUpButtonDown = false;
    _speedDownButtonDown = false;
    
    // Sticker
    _stickerBackground = CreateSprite("sticker_back.pvr", StickerBackgroundRenderQueue, Vector2(100,100), Vector2(50,50));
    _stickerButton = CreateSprite("sticker.pvr", StickerRenderQueue, Vector2(50,50), Vector2(50,50));
    
    // Speed up button
    
    Vector2 speedButtonSize = Vector2(SpeedButtonWidth, SpeedButtonHeight);
    Vector2 resolution = utils::GetInputResolution();
    Vector2 pos;
    
    pos = resolution - Vector2(speedButtonSize.x / 2 + 20, speedButtonSize.y * 2);
    _speedUpButton = CreateButton("SpeedButton.pvr", SpeedButtonRenderQueue, speedButtonSize, pos, false);
    
    pos = resolution - Vector2(speedButtonSize.x / 2 + 20, speedButtonSize.y - 10);
    _speedDownButton = CreateButton("SpeedButton.pvr", SpeedButtonRenderQueue, speedButtonSize, pos, true);
}

//------------------------------------------------------------------------------

void TouchGameUI::Update() {

	// Getting values from TouchPlayerController
	TouchPlayerControllerGetDataEvent getDataEvent;
	// Received in TouchPlayerController.
	if (DispatchEvent(&getDataEvent, EventDispatchGlobalBroadcast)) {
		// Applying values
		SetStickerEnabled(getDataEvent.stickerEnabled);
		ConfigureSticker(&getDataEvent);
	} else {
		SetStickerEnabled(false);		
	}
	
	//
	
	TouchGameUIButtonEvent buttonEvent;
	buttonEvent.speedUp = _speedUpButtonDown;
	buttonEvent.speedDown = _speedDownButtonDown;

	// Received in TouchPlayerController
	DispatchEvent(&buttonEvent, EventDispatchGlobalBroadcast);
}

//******************************************************************************
// ButtonDelegate

void TouchGameUI::ButtonDown(Button *button) {
    
    if (button == _speedUpButton) {
        _speedUpButtonDown = true;
    } else if (button == _speedDownButton) {
        _speedDownButtonDown = true;        
    }
}

//------------------------------------------------------------------------------

void TouchGameUI::ButtonUp(Button *button) {
    
    if (button == _speedUpButton) {
        _speedUpButtonDown = false;
    } else if (button == _speedDownButton) {
        _speedDownButtonDown = false;        
    }
}

//******************************************************************************
//
//  Private
//
//******************************************************************************

void TouchGameUI::SetStickerEnabled(bool enabled) {
    
    _stickerBackground->Active(enabled);
    _stickerButton->Active(enabled);
}

//------------------------------------------------------------------------------

void TouchGameUI::ConfigureSticker(TouchPlayerControllerGetDataEvent *event) {
    
    _stickerBackground->Position(Vector2(event->initialStickerPos));
    _stickerButton->Position(Vector2(event->currentStickerPos));
    _stickerBackground->Size(Vector2(event->stickerRadius * 2.0f));
}

//------------------------------------------------------------------------------

SpriteRenderer *TouchGameUI::CreateSprite(const std::string &texture, int renderQueue, Vector2 size, Vector2 position) {
    
    SpriteRenderer *result = GameObject()->AddComponent<SpriteRenderer>();
	Material stickerMaterial = getdata::MaterialGUI(texture, renderQueue);
	result->Material(stickerMaterial);
	result->UseTransform(false);
	result->Size(size);
	result->Position(position);
    
    return result;
}

//------------------------------------------------------------------------------

Button *TouchGameUI::CreateButton(const std::string &texture, int RenderQueue, const Vector2 &size, const Vector2 &position, bool invertY) {
    
    Button *result = GameObject()->AddComponent<Button>(); 
    
    Material speedButtonMaterial = getdata::MaterialGUI("SpeedButton.pvr", SpeedButtonRenderQueue);
    result->Material(speedButtonMaterial);
    
    result->Size(size);
    result->Position(position);
    result->InvertY(invertY);
    result->Delegate(this);
    
    return result;
}
