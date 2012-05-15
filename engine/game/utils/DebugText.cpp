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
#include <sstream>
#include "RenderPipeline.h"

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
	_textRenderer->CharacterSize(15);
	_textRenderer->Is3D(false);
	_textRenderer->Position(Vector2(10,30));
	_textRenderer->Text("Some text!");
}


void DebugText::Update() {
    
    RenderPipeline *pipeline = GameObject()->RenderPipeline();
    
    std::stringstream stream;
    stream << "FPS: " << pipeline->GetFPS() << std::endl;
    stream << "Draw Calls: " << pipeline->GetDipCount() << std::endl;
    stream << "Texture switches: " << pipeline->GetTextureSwitchCount() << std::endl;
    stream << "Shader switches: " << pipeline->GetShaderSwitchCount() << std::endl;
    stream << "Mesh switches: " << pipeline->GetMeshSwitchCount() << std::endl;
    
    _textRenderer->Text(stream.str());
}