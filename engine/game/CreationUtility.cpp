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
#include "PlayerController.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "CameraMover.h"
#include "Sphere.h"
#include "Font.h"

namespace creation {

	static Scene *scene;
	
	void Init(Scene *theScene) {
		
		scene = theScene;
	}
	
	void InitLevel() {
		
		CreatePlayer(Vector3(0,0,0));
		CreateCamera(Vector3(0,0,50));
		GameObject *boxField = CreateBoxField(Vector3(0,0,0), 15);
//		physics::ConfigureAsCollisionGeometry(boxField, true, false);
		
		
		CreateWorldContainer();
	}

	
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
	
	
	GameObject *CreateBox(const Vector3 &position) {
	
		Prefab *boxPrefab = resource::GetPrefab("cube.mdl");
		GameObject *box = boxPrefab->Instantiate();
		box->Name("Box");
		box->Transform()->Position(position);
		
		Material material;
		
		Font *font = resource::GetFont("Arial.ttf");
		
		material.Texture(font->FontTexture());
//		material.Texture(resource::GetTexture("crate.pvr"));
		material.Shader(resource::GetShader("SimpleShader"));
		box->SetMaterial(material, true);
		
		return box;
	}
	

	GameObject *CreatePlayer(const Vector3 &position) {

		float PLAYER_SHIP_RADIUS = 2;
		
		Prefab *playerPrefab = resource::GetPrefab("PlayerShip.mdl");
		GameObject *playerGO = playerPrefab->Instantiate();
		playerGO->Name("Player");
		playerGO->Transform()->Position(position);
		
		playerGO->AddComponent<PlayerShip>();
		playerGO->AddComponent<PlayerController>();
		Rigidbody* body = playerGO->AddComponent<Rigidbody>();
		
		Material material;
		material.Texture(resource::GetTexture("avatar.pvr"));
		material.Shader(resource::GetShader("SimpleShader"));
		playerGO->SetMaterial(material, true);
		
		body->SetAsSphere(PLAYER_SHIP_RADIUS);
		body->Mass(1);
		
		return playerGO;
	}


	GameObject *CreateCamera(const Vector3 &position) {
		
		GameObject *cameraGO = scene->CreateGameObject("Camera");
		cameraGO->Transform()->Position(position);
		
		cameraGO->AddComponent<Camera>();
//		cameraGO->AddComponent<CameraMover>();
		
		return cameraGO;
	}

	
	GameObject *CreateWorldContainer() {

		Prefab *worldContainerPrefab = resource::GetPrefab("sphere.mdl");
		GameObject *worldContainer = worldContainerPrefab->Instantiate();
		worldContainer->AddComponent<Sphere>();
		return worldContainer;
	}


}