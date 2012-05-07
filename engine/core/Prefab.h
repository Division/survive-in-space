//
//  Prefab.h
//  Cpptest
//
//  Created by Nikita on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PREFAB_H
#define PREFAB_H

#include <string>
#include <vector>
#include "Scene.h"
#include "Render.h"
#include "Resource.h"

typedef std::unique_ptr<Mesh> MeshPtr;
typedef std::vector<MeshPtr> MeshList;

class Prefab {
public:
	
	Prefab(const std::string& name = "", Scene *scene = NULL);
	~Prefab();
	
	bool Load(const std::string& filename);
	bool Load(std::istream& stream, GameObject **outGameObject);
	
	void Scene(class Scene* scene) { _scene = scene; }
	class Scene *Scene() const { return _scene; }
	
	void Name(const std::string& name) { _name = name; }
	const std::string& Name() const { return _name; }
	
	GameObject *Instantiate();
	
private:
	GameObject *CreateGameObject();
	Mesh *CreateMesh();
	void CopyGameObject(GameObject *source, GameObject *target);
	
private:
	GameObject *_rootGameObject;
	bool _isValid;
	std::string _name;
	class Scene *_scene;
	
	GameObjectList _gameObjects;
	MeshList _meshList;
};

#endif
