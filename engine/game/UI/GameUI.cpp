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

//******************************************************************************
//
//  Public
//
//******************************************************************************

void GameUI::Awake() {

    _playerController = NULL;
    
	_stickerBackground = GameObject()->AddComponent<SpriteRenderer>();
	Material backgroundMaterial = getdata::MaterialUnlitTexture("sticker_back.pvr", StickerBackgroundRenderQueue, BlendFuncTransparent);
	backgroundMaterial.DepthTest(false);
	_stickerBackground->Material(backgroundMaterial);
	_stickerBackground->UseTransform(false);
	_stickerBackground->Size(Vector2(100,100));
	_stickerBackground->Position(Vector2(100,100));
	
	_stickerButton = GameObject()->AddComponent<SpriteRenderer>();
	Material stickerMaterial = getdata::MaterialUnlitTexture("sticker.pvr", StickerRenderQueue, BlendFuncTransparent);
	stickerMaterial.DepthTest(false);
	_stickerButton->Material(stickerMaterial);
	_stickerButton->UseTransform(false);
	_stickerButton->Size(Vector2(50,50));
	_stickerButton->Position(Vector2(100,100));
}

//------------------------------------------------------------------------------

void GameUI::Update() {
	
    if (_playerController) { // Player object found. Use his controller to position buttons
        SetStickerEnabled(_playerController->StickerEnabled());
        
        if (_playerController->Active()) {
            ConfigureSticker(_playerController);
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

