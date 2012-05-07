//
//  SceneGraph.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <vector>

class GameObject;
class Scene;

struct SceneGraphNode;
typedef std::vector<SceneGraphNode> SceneGraphNodeList;

struct SceneGraphNode {
	SceneGraphNode *parentNode;
	GameObject *gameObject;
	SceneGraphNodeList childNodes;
};


class SceneGraph {
public:
	SceneGraph();
	~SceneGraph();
	
	void Scene(class Scene *scene) { _scene = scene; };
	class Scene* Scene() const { return _scene; }
	
	void PrintHierarchy() const;
	
	const SceneGraphNode &RootNode() const { return _rootNode; };
	
	void Rebuild(void);
	
private:
	
	
private:
	SceneGraphNode _rootNode;
	class Scene *_scene;
};




#endif
