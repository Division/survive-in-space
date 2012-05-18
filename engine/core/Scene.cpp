//
//  Scene.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Scene.h"
#include "Input.h"
#include "CreationUtility.h"
#include "Platform.h"
#include "Utils.h"
#include "RenderPipeline.h"
#include "RenderState.h"
#include "Font.h"

//******************************************************************************
// Constructor/destructor

Scene::Scene(class Platform *platform) {
	
	_sceneGraph.Scene(this);
	_platform = platform;
	input::Init(platform);
	utils::Init(platform);
	resource::Init(this);
	freetype::Init();
	
	#ifdef ENABLE_PHYSICS
	physics::Init(this);
	#endif
	
	creation::Init(this);
	RenderState *renderState = new RenderState();
	_renderPipeline = RenderPipelinePtr(new RenderPipeline(renderState));
	_renderState = RenderStatePtr(renderState);
}

//------------------------------------------------------------------------------

Scene::~Scene(void) {
	
}

//******************************************************************************
// ObjectSearch

GameObject *Scene::SearchGameObject(const std::string &objectName) {
    
    GameObject *result = NULL;
	for (GameObjectList::iterator it = _gameObjects.begin(); it != _gameObjects.end(); it++) {
        if ((*it)->Name() == objectName) {
            result = it->get();
            break;
        }
    }

    if (!result) {
        for (GameObjectList::iterator it = _gameObjects.begin(); it != _gameObjects.end(); it++) {
            Transform *transform = (*it)->Transform()->Find(objectName);
            if (transform) {
                result = transform->GameObject();
                break;
            }
        }
    }
    
    return result;
}

//******************************************************************************
// GameObjects and hierarchy

GameObject *Scene::CreateGameObject(std::string name) {
	
	GameObject *object = new GameObject(name);
	object->RenderPipeline(_renderPipeline.get());
	object->ObjectSearch(this);
    
	_objectsToAdd.push_back(std::move(GameObjectPtr(object)));
	
	return object;
}

//------------------------------------------------------------------------------

void Scene::MoveAddedObjectsToScene() {
	
	for (GameObjectList::iterator it = _objectsToAdd.begin(); it != _objectsToAdd.end(); it++) {
		(*it)->InHierarchy(true);
		(*it)->PreStart();		
		(*it)->Start();
		_gameObjects.push_back(std::move((*it)));
	}
	
	_objectsToAdd.clear();
}

//******************************************************************************
// Render

void ProcessPreRender(const GameObjectPtr&object) {
	
	if (object->Active()) {
		object->PreRender();
	}
}

//------------------------------------------------------------------------------

void ProcessRender(const GameObjectPtr& object) {
	
	if (object->Active()) {
		object->Render();
	}
}

//------------------------------------------------------------------------------

void Scene::Render() {
	
	_renderPipeline->PreparePipeline(_gameObjects.size(), Camera::Main());
	
	std::for_each(_gameObjects.begin(), _gameObjects.end(), ProcessRender);

	_renderPipeline->Render();
	
	#ifdef ENABLE_PHYSICS
	physics::Render();
	#endif
}

//******************************************************************************
// Transform

void ProcessTransform(SceneGraphNode &node) {
	
	if (node.gameObject->Active()) {
		node.gameObject->Transform()->CalculateTransformMatrix(true);
	}
}	

//------------------------------------------------------------------------------

void Scene::UpdateTransforms() {
	
	SceneGraphNode rootNode = Graph()->RootNode();
	std::for_each(rootNode.childNodes.begin(), rootNode.childNodes.end(), ProcessTransform);
}

//******************************************************************************
// Update

void ProcessPreUpdate(const GameObjectPtr& object) {

	if (object->Active()) {
		object->PreUpdate();
	}
}

//------------------------------------------------------------------------------

void ProcessUpdate(const GameObjectPtr& object) {
	
	if (object->Active()) {
		object->Update();
	}
}

//------------------------------------------------------------------------------

void Scene::Update() {

	MoveAddedObjectsToScene();
	_sceneGraph.Rebuild();
	UpdateTransforms();
	physics::Update();
	
	std::for_each(_gameObjects.begin(), _gameObjects.end(), ProcessPreUpdate);
	std::for_each(_gameObjects.begin(), _gameObjects.end(), ProcessUpdate);
	std::for_each(_gameObjects.begin(), _gameObjects.end(), ProcessPreRender);

	utils::Update();
//	input::PrintTouchesCount();
}

//******************************************************************************
// IPhysicsCallbackReceiver

#ifdef ENABLE_PHYSICS

void ProcessPhysicsTick(const GameObjectPtr& object) {
	
	object->PhysicsTick();
}

//------------------------------------------------------------------------------

void Scene::PhysicsTickCallback(float timeStep) {
	
	std::for_each(_gameObjects.begin(), _gameObjects.end(), ProcessPhysicsTick);
}

#endif	

