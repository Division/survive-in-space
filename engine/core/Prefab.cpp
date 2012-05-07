//
//  Prefab.cpp
//  Cpptest
//
//  Created by Nikita on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Prefab.h"
#include "Utils.h"
#include <fstream>

Prefab::Prefab(const std::string& name, class Scene *scene) {
	
	_name = name;
	_scene = scene;
	_isValid = false;
}


Prefab::~Prefab() {
	
}

bool Prefab::Load(const std::string& filename) {

	if (_isValid) return false;
	
	bool result = false;
	
	std::string path;
	if (utils::GetResourcePath(filename, path)) {
		std::ifstream stream(path, std::ios::binary);
		result = Load(stream, &_rootGameObject);
	} else {
		utils::Log("Can't find prefab file: " + filename);
	}
	
	if (!result) {
		utils::Log("Error loading prefab: " + filename);
	}
	
	_isValid = result;
	return result;
}


bool Prefab::Load(std::istream& stream, GameObject **outGameObject) {

	if (_isValid) return false;
	
	bool result = true;
	
	try {
		stream.exceptions(std::ios::badbit | std::ios::failbit);
		
		unsigned short nameLength;
		stream.read((char *)&nameLength, sizeof(unsigned short));
		std::string name = "";
		if (nameLength >= 0 && nameLength < 100) {
			name.resize(nameLength, ' ');
			if (nameLength > 0) {
				stream.read(&name[0], nameLength);
			}
		} else {
			utils::Log("Incorrect object name length");
			return false;
		}
		
		int childCount;
		stream.read((char *)&childCount, sizeof(int));
		char hasMesh;
		stream.read(&hasMesh, sizeof(char));
		Vector3 position;
		stream.read((char *)&position, sizeof(Vector3));
		Quaternion rotation;
		stream.read((char *)&rotation, sizeof(Quaternion));
		
		GameObject *object = CreateGameObject();
		object->Name(name);
		object->Transform()->Position(position);
		object->Transform()->Rotation(rotation);
		
		if (hasMesh > 0) {
			MeshRenderer *renderer = object->AddComponent<MeshRenderer>();
			Mesh *mesh = CreateMesh();
			renderer->Mesh(mesh);
			if (!mesh->Load(stream, true)) return false;
		}
		*outGameObject = object;
		
		for (int i = 0; i < childCount; i++) {
			GameObject *child;
			if (Load(stream, &child)) {
				child->Transform()->Parent(object->Transform());
			} else {
				utils::Log("Error loading child object");
				return false;
			}
		}
		
	} catch (std::exception e) {
		result = false;
		utils::Log("Error reading object stream");
	}
	
	return result;
}


GameObject *Prefab::CreateGameObject() {
	
	GameObject *object = new GameObject();
	_gameObjects.push_back(std::move(GameObjectPtr(object)));
	return object;
}


Mesh *Prefab::CreateMesh() {

	Mesh *mesh = new Mesh();
	_meshList.push_back(std::move(MeshPtr(mesh)));
	return mesh;
}

void Prefab::CopyGameObject(GameObject *source, GameObject *target) {
	
	if (source->Renderer()) {
		MeshRenderer *renderer = target->AddComponent<MeshRenderer>();
		renderer->Material(source->Renderer()->Material());
		renderer->Mesh(source->Renderer()->Mesh());
	}
	
	target->Transform()->Position(source->Transform()->Position());
	target->Transform()->Rotation(source->Transform()->Rotation());
	
	TransformList children = source->Transform()->Children();
	for (TransformList::iterator it = children.begin(); it != children.end(); it++) {
		GameObject *child = (*it)->GameObject();
		GameObject *newChild = _scene->CreateGameObject(child->Name());
		CopyGameObject(child, newChild);
		newChild->Transform()->Parent(target->Transform());
	}
}

GameObject *Prefab::Instantiate() {
	
	GameObject *object = _scene->CreateGameObject(_name);
	CopyGameObject(_rootGameObject, object);
	return object;
}

