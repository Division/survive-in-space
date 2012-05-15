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

static const int StickerBackgroundRenderQueue = RenderQueueOverlay + 10;
static const int StickerRenderQueue = StickerBackgroundRenderQueue + 1;

//******************************************************************************
//
//  Public
//
//******************************************************************************

void GameUI::Awake() {

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
	
}

//------------------------------------------------------------------------------

void GameUI::PreRender() {
	
}
