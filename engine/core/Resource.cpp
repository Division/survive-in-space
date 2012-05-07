//
//  Resources.cpp
//  Cpptest
//
//  Created by Nikita on 4/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Prefab.h"
#include "Scene.h"
#include "Render.h"
#include <string>
#include <map>

namespace resource {
	
	static Scene *mainScene;
	static manager::TextureManager textureManager;
	static manager::ShaderManager shaderManager;
	static manager::PrefabManager prefabManager;
	
	Texture *GetTexture(const std::string& name) {
		
		return textureManager.GetResource(name);
	}
	
	
	Shader *GetShader(const std::string& name) {
		
		return shaderManager.GetResource(name);
	}
	
	
	Prefab *GetPrefab(const std::string& name) {

		Prefab *prefab = prefabManager.GetResource(name);
		prefab->Name(name);
		prefab->Scene(mainScene);
		return prefab;
	}

	
	
	
	void Init(Scene *scene) {
		
		mainScene = scene;
	}
	
}

