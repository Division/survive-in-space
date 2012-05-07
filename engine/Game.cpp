//
//  Game.cpp
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Game.h"
#include "Scene.h"
#include "CreationUtility.h"

Scene *scene;

void Game::Render(const Vector4& viewport) {
    
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	scene->Render();
}

void Game::Update(float deltaTime) {
    
	scene->Update();
}

void Game::Init(Platform *platform) {
	
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	scene = new Scene(platform);
	creation::InitLevel();

	scene->Update();
	scene->Graph()->PrintHierarchy();
}

void Game::Finalize() {
    
	delete scene;
}
