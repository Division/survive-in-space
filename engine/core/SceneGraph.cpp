//
//  SceneGraph.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SceneGraph.h"
#include "GameObject.h"
#include "Scene.h"
#include "Utils.h"

SceneGraph::SceneGraph() {
	
}


SceneGraph::~SceneGraph() {
	
}


void FillNodeChildren(SceneGraphNode& node) {
	
	GameObject *object = node.gameObject;

	const Transform *transform = object->Transform();
	const TransformList& childTransforms = transform->Children();
	for (TransformList::const_iterator it = childTransforms.begin(); it != childTransforms.end(); it++) {
		GameObject *childObject = (*it)->GameObject();

		SceneGraphNode childNode;
		
		childNode.parentNode = &node;
		childNode.gameObject = childObject;
		FillNodeChildren(childNode);
		node.childNodes.push_back(childNode);
	}
}


void FillNodeListWithNullParentObjects(SceneGraphNode& node, const GameObjectList& gameObjectList) {
	
	for (GameObjectList::const_iterator it = gameObjectList.begin(); it != gameObjectList.end(); it++) {
		if (it->get()->Transform()->Parent() == NULL) {
			SceneGraphNode childNode;
			childNode.gameObject = it->get();
			childNode.parentNode = &node;
			
			FillNodeChildren(childNode);
			
			node.childNodes.push_back(childNode);
		}
	}
}


void SceneGraph::Rebuild(void) {

	_rootNode.childNodes.clear();
	_rootNode.parentNode = NULL;
	_rootNode.gameObject = NULL;
	
	// Get transforms with no parent and fill them
	FillNodeListWithNullParentObjects(_rootNode, _scene->ObjectList());
}


void PrintNode(const SceneGraphNode& node, int depth = 0) {
	
	std::string offset = "";
	for (int i = 0; i < depth; i++) {
			offset += "    ";
	}
	
	if (node.gameObject) {
		utils::Log(offset + node.gameObject->Name());
	}
	
	for (SceneGraphNodeList::const_iterator it = node.childNodes.begin(); it != node.childNodes.end(); it++) {
		PrintNode(*it, depth + 1);
	}
}


void SceneGraph::PrintHierarchy() const {
	utils::Log("Root");
	PrintNode(_rootNode);
}
