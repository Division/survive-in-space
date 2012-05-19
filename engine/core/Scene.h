//
//  Scene.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Cpptest_Scene_h
#define Cpptest_Scene_h

#include <memory>
#include <vector>
#include "GameObject.h"
#include "ComponentDeclaration.h"
#include "SceneGraph.h"
#include "ObjectSearch.h"
#include "Event.h"

#ifdef ENABLE_PHYSICS
#include "Physics.h"
#endif

class Platform;
class Component;
class GameObject;
class RenderPipeline;
class RenderState;

typedef std::unique_ptr<GameObject> GameObjectPtr;
typedef std::vector<GameObjectPtr> GameObjectList;
typedef std::unique_ptr<RenderPipeline> RenderPipelinePtr;
typedef std::unique_ptr<RenderState> RenderStatePtr;

class Scene
: public ObjectSearch
#ifdef ENABLE_PHYSICS
, public physics::IPhysicsCallbackReceiver 
#endif
{
public:
	
	Scene(class Platform *platform);
	~Scene(void);

	//******************************************************************************
	// ObjectSearch
    
    virtual GameObject *SearchGameObject(const std::string &objectName);
    
	//******************************************************************************
	// Platform
	
	class Platform *Platform() { return _platform; }
	
	//******************************************************************************
	// GameObjects and hierarchy
	
	GameObject *CreateGameObject(std::string name);
	
	const GameObjectList& ObjectList() { return _gameObjects; }
	
	const SceneGraph* Graph() { return &_sceneGraph; }
	
	//******************************************************************************
	// Render/update
	
	void Render();
	
	void Update();
	
	//******************************************************************************
	// IPhysicsCallbackReceiver

	#ifdef ENABLE_PHYSICS
	void PhysicsTickCallback(float timeStep);
	#endif
	
private:
	void MoveAddedObjectsToScene();
	void UpdateTransforms();
	
private:
	GameObjectList _objectsToAdd;
	GameObjectList _gameObjects;
	SceneGraph _sceneGraph;
	class Platform *_platform;
	RenderPipelinePtr _renderPipeline;
	RenderStatePtr _renderState;
	EventDispatcher _globalDispatcher;
};

#endif
