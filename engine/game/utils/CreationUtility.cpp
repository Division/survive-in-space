//
//  CreationUtility.cpp
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CreationUtility.h"
#include "Scene.h"
#include "Physics.h"
#include "GameObject.h"
#include "Resource.h"
#include "Prefab.h"
#include "Rigidbody.h"
#include "PlayerShip.h"
#include "TouchPlayerController.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "CameraMover.h"
#include "Sphere.h"
#include "Font.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "DebugText.h"
#include "TouchGameUI.h"
#include "Button.h"

namespace creation {

	//******************************************************************************
	// Scene and level
	
	static Scene *scene;
	
	void Init(Scene *theScene) {
		
		scene = theScene;
	}
	
	//------------------------------------------------------------------------------
	
	void InitLevel() {
		
		CreateDebugText();
		CreateGameUI();
		CreatePlayer(Vector3(0,0,0));
		CreateCamera(Vector3(0,0,50));
		GameObject *boxField = CreateBoxField(Vector3(0,0,0), 15);
//		physics::ConfigureAsCollisionGeometry(boxField, true, false);
		
//		CreateTextLabel("Hello\nTexture\nFont\nRender.", Vector3(100,30,0));
//		CreateTextLabel("Hello Texture Font Render.", Vector3(100,100,0));
//		CreateTextLabel("hello texture foxnt render.", Vector3(100,100,0));
//		CreateTextLabel("NUll", Vector3(100,100,0));
		
		CreateWorldContainer();
	}

	//------------------------------------------------------------------------------
	
	GameObject *CreateWorldContainer() {
		
		Prefab *worldContainerPrefab = resource::GetPrefab("sphere.mdl");
		GameObject *worldContainer = worldContainerPrefab->Instantiate();
		worldContainer->AddComponent<Sphere>();
		return worldContainer;
	}
	
	//******************************************************************************
	// Geometry
	
	GameObject *CreateBox(const Vector3 &position) {
	
		Prefab *boxPrefab = resource::GetPrefab("cube.mdl");
		GameObject *box = boxPrefab->Instantiate();
		box->Name("Box");
		box->Transform()->Position(position);
		
		Material material;
		
		material.Texture(resource::GetTexture("crate.pvr"));
		material.Shader(resource::GetShader("SimpleShader"));
		box->SetMaterial(material, true);
		
		return box;
	}
	
	TextRenderer *CreateTextLabel(std::string text, const Vector3 &position) {
		
		GameObject *textObject = scene->CreateGameObject("Text");
		TextRenderer *textRenderer = textObject->AddComponent<TextRenderer>();
		
		Material material;
		material.Shader(resource::GetShader("SimpleShader"));
		material.RenderQueue(RenderQueueOverlay);
		textRenderer->Material(material);
		
		textRenderer->CharacterSize(20);
		
		textRenderer->Is3D(false);
		Font *font = resource::GetFont("Arial.ttf");
		textRenderer->Font(font);
		textRenderer->Text(text);
		textRenderer->Position(Vector2(position));
		
		return textRenderer;
	}
	
	//------------------------------------------------------------------------------
	
	GameObject *CreateBoxField(const Vector3& offset, float distance) {
		
		GameObject *field = scene->CreateGameObject("BoxField");
		
		const int COUNT_X = 3;
		const int COUNT_Y = 3;
		const int COUNT_Z = 3;
		const Vector3 SHIFT_TO_CENTER = Vector3((COUNT_X-1) * distance / 2.0, (COUNT_Y-1) * distance / 2.0, (COUNT_Z-1) * distance / 2.0);
		
		for (int i = 0; i < COUNT_X; i++) {
			for (int j = 0; j < COUNT_Y; j++) {
				for (int k = 0; k < COUNT_Z; k++) {
					Vector3 pos = Vector3(i * distance, j * distance, k * distance);
					CreateBox(pos + offset - SHIFT_TO_CENTER)->Transform()->Parent(field->Transform());
				}
			}
		}
		
		return field;
	}

	//******************************************************************************
	// Player

	GameObject *CreatePlayer(const Vector3 &position) {

		float PLAYER_SHIP_RADIUS = 2;
		
		Prefab *playerPrefab = resource::GetPrefab("PlayerShip.mdl");
		GameObject *playerGO = playerPrefab->Instantiate();
		playerGO->Name("Player");
		playerGO->Transform()->Position(position);
		
		playerGO->AddComponent<PlayerShip>();
		playerGO->AddComponent<TouchPlayerController>();
		Rigidbody* body = playerGO->AddComponent<Rigidbody>();
		
		Material material;
		material.Texture(resource::GetTexture("avatar.pvr"));
		material.Shader(resource::GetShader("SimpleShader"));
		playerGO->SetMaterial(material, true);
		
		body->SetAsSphere(PLAYER_SHIP_RADIUS);
		body->Mass(1);
		
/*		Font *font = resource::GetFont("Arial.ttf");
		material.Texture(font->FontTexture());
		material.Shader(resource::GetShader("SimpleShader"));
		material.RenderQueue(RenderQueueOverlay);
		material.DepthWrite(false);
		material.DepthTest(false);
		SpriteRenderer *sprite = playerGO->AddComponent<SpriteRenderer>();
		sprite->Material(material);
		sprite->Size(Vector2(200,200));
		sprite->Position(Vector2(200,200));
		sprite->UseTransform(false);*/
		
		return playerGO;
	}

	//******************************************************************************
	// Camera

	GameObject *CreateCamera(const Vector3 &position) {
		
		GameObject *cameraObject = scene->CreateGameObject("Camera");
		cameraObject->Transform()->Position(position);
		
		cameraObject->AddComponent<Camera>();
		
		return cameraObject;
	}
	
	//******************************************************************************
	// Utils
	
	GameObject *CreateDebugText() {

		GameObject *debugTextObject = scene->CreateGameObject("DebugText");
		DebugText *debugText = debugTextObject->AddComponent<DebugText>();
		return debugTextObject;
	}

	//******************************************************************************
	// UI
	
	TouchGameUI *CreateGameUI() {

		GameObject *gameUIObject = scene->CreateGameObject("GameUI");
		TouchGameUI *gameUI = gameUIObject->AddComponent<TouchGameUI>();

		return gameUI;
	}
    
    //------------------------------------------------------------------------------
    
    Button *CreateButton(Texture *texture, float width, float height, int renderQueue) {
        
        GameObject *buttonObject = scene->CreateGameObject("Button");
        Button *button = buttonObject->AddComponent<Button>();
        button->SetTexture(texture);
        button->Material().RenderQueue(renderQueue);
        button->Size(Vector2(width, height));
        
        return button;
    }

}