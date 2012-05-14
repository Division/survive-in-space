//
//  DebugText.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "DebugText.h"
#include "TextRenderer.h"
#include "GameObject.h"
#include "GetData.h"

//******************************************************************************
//
//  Component
//
//******************************************************************************

void DebugText::Awake() {

	_textRenderer = GameObject()->AddComponent<TextRenderer>();
	_textRenderer->Material(getdata::MaterialUnlitTexture("", RenderQueueOverlay));
	Font *font = resource::GetFont("Arial.ttf");
	_textRenderer->Font(font);
	_textRenderer->CharacterSize(20);
	_textRenderer->Is3D(false);
	_textRenderer->Position(Vector2(10,30));
	_textRenderer->Text("Some text!");
}