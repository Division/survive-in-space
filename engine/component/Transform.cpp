//
//  Transform.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Transform.h"
#include "GameObject.h"

Transform::Transform() {
	
	_forceWorldTransform = false;
	_parent = NULL;
}


Transform::~Transform() {
	
	
}


void Transform::Position(const Vector3& position) {
	
	_position = position;
}


void Transform::Rotation(const Quaternion& rotation) {
	
	_rotation = rotation;
}


void Transform::Parent(Transform *parent) {

	// Remove from current parent
	if (_parent) {
		_parent->RemoveChild(this);
	}
	
	// Setting new parent
	_parent = parent;
	
	// new parent could be NULL - top level hierarchy
	if (_parent) {
		_parent->AddChild(this);
	}
}


Transform *Transform::RootParent() const {

	Transform *result = const_cast<Transform *>(this);
	
	if (_parent) {
		result = _parent->RootParent();
	}
	
	return result;
}


void Transform::RemoveChild(Transform *child) {

	_children.erase(std::remove(_children.begin(), _children.end(), child));
}


void Transform::AddChild(Transform *child) {
	
	// Add if not exists
	if (std::find(_children.begin(), _children.end(), child) == _children.end()) {
		_children.push_back(child);
	}
}

Vector3 Transform::Right() const {
	
	Vector3 result = math::Rotate(Vector3(1,0,0), _rotation);
	return result;
}


Vector3 Transform::Up() const {

	Vector3 result = math::Rotate(Vector3(0,1,0), _rotation);
	return result;
}


Vector3 Transform::Forward() const {

	Vector3 result = math::Rotate(Vector3(0,0,1), _rotation);
	return result;
}


Matrix4 Transform::GetRTMatrix(const Vector3& position, const Quaternion& rotation) {
	
	Matrix4 matrix = math::Translation(position);
	Matrix4 rotationMatrix = glm::mat4_cast(rotation);
	matrix = matrix * rotationMatrix;

	return matrix;
}


void Transform::CalculateTransformMatrix(bool recursively) {
	
	if (Parent() && !_forceWorldTransform) {
		_transformToWorldMatrix = Parent()->TransformToWorldMatrix() * GetRTMatrix(_position, _rotation);
	} else {
		_transformToWorldMatrix = GetRTMatrix(_position, _rotation);
	}
	
	if (recursively) {
		for (TransformList::iterator it = _children.begin(); it != _children.end(); it++) {
			(*it)->CalculateTransformMatrix(recursively);
		}
	}
}


Transform *Transform::Find(const std::string& name) const {

	Transform *result = NULL;
	
	for (TransformList::const_iterator it = _children.begin(); it != _children.end(); it++) {
		if ((*it)->GameObject()->Name() == name) {
			result = *it;
			break;
		}
	}
	
	if (!result) {
		for (TransformList::const_iterator it = _children.begin(); it != _children.end(); it++) {
			result = (*it)->Find(name);
			if (result) break;
		}
	}
	
	return result;
}