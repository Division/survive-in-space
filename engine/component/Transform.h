//
//  Transform.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "MyMath.h"
#include <vector>

class Transform;
typedef std::vector<Transform*> TransformList;

class Transform : public Component {
public:
	GENERATE_COMPONENT_ID(Transform)
	
	Transform();
	~Transform();
	
	const Vector3 Position(void) const { return _position; }
	void Position(const Vector3& position);
	
	const Quaternion Rotation(void) const { return _rotation; }
	void Rotation(const Quaternion& rotation);
	
	Transform *Parent() const { return _parent; };
	void Parent(Transform *parent);
	Transform *RootParent() const;
	
	const TransformList& Children() const { return _children; };
	
	const Matrix4& TransformToWorldMatrix() const { return _transformToWorldMatrix; }
	
	void CalculateTransformMatrix(bool recursively = false);
	
	static Matrix4 GetRTMatrix(const Vector3& position, const Quaternion& rotation);
	
	Transform *Find(const std::string& name) const;
	
	bool ForceWorldTransform() const { return _forceWorldTransform; }
	void ForceWorldTransform(bool force) { _forceWorldTransform = force; }
	
	Vector3 Right() const;
	Vector3 Up() const;
	Vector3 Forward() const;
	
private:
	void RemoveChild(Transform *child);
	void AddChild(Transform *child);
	
private:
	bool _forceWorldTransform;
	Vector3 _position;
	Quaternion _rotation;
	Matrix4 _transformToWorldMatrix;

	TransformList _children;
	mutable Transform *_parent;
};


#endif
