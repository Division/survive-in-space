//
//  GameUI.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameUI.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "GetData.h"
#include "Resource.h"
#include "PlayerController.h"
#include "Transform.h"

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

void GameUI::Awake() {

    _playerController = NULL;
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

void GameUI::Update() {
	
    if (_playerController) { // Player object found. Use his controller to position buttons
        SetStickerEnabled(_playerController->StickerEnabled());
        
        if (_playerController->Active()) {
            ConfigureSticker(_playerController);
            _playerController->SetSpeedButtonsState(_speedUpButtonDown, _speedDownButtonDown);
        }
        
    } else { // Search for player object
        
        SetStickerEnabled(false);
        
        class GameObject *playerObject = GameObject()->SearchGameObject("Player");
        if (playerObject) {
            _playerController = playerObject->GetComponent<PlayerController>();
        }
        
    }
}

//------------------------------------------------------------------------------

void GameUI::PreRender() {
	
}

//******************************************************************************
// ButtonDelegate

void GameUI::ButtonDown(Button *button) {
    
    if (button == _speedUpButton) {
        _speedUpButtonDown = true;
    } else if (button == _speedDownButton) {
        _speedDownButtonDown = true;        
    }
}

//------------------------------------------------------------------------------

void GameUI::ButtonUp(Button *button) {
    
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

void GameUI::SetStickerEnabled(bool enabled) {
    
    _stickerBackground->Active(enabled);
    _stickerButton->Active(enabled);
}

//------------------------------------------------------------------------------

void GameUI::ConfigureSticker(PlayerController *controller) {
    
    _stickerBackground->Position(Vector2(controller->InitialStickerPos()));
    _stickerButton->Position(Vector2(controller->CurrentStickerPos()));
    _stickerBackground->Size(Vector2(controller->StickerRadius() * 2.0f));
    
}

//------------------------------------------------------------------------------

SpriteRenderer *GameUI::CreateSprite(const std::string &texture, int renderQueue, Vector2 size, Vector2 position) {
    
    SpriteRenderer *result = GameObject()->AddComponent<SpriteRenderer>();
	Material stickerMaterial = getdata::MaterialGUI(texture, renderQueue);
	result->Material(stickerMaterial);
	result->UseTransform(false);
	result->Size(size);
	result->Position(position);
    
    return result;
}

//------------------------------------------------------------------------------

Button *GameUI::CreateButton(const std::string &texture, int RenderQueue, const Vector2 &size, const Vector2 &position, bool invertY) {
    
    Button *result = GameObject()->AddComponent<Button>(); 
    
    Material speedButtonMaterial = getdata::MaterialGUI("SpeedButton.pvr", SpeedButtonRenderQueue);
    result->Material(speedButtonMaterial);
    
    result->Size(size);
    result->Position(position);
    result->InvertY(invertY);
    result->Delegate(this);
    
    return result;
}
