//
//  Collider.cpp
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Rigidbody.h"

#ifdef ENABLE_PHYSICS

#include "Utils.h"
#include "Transform.h"
#include "Render.h"
#include "GameObject.h"

//******************************************************************************
// Constructor/destructor

Rigidbody::Rigidbody() {
	
	_collisionShapeSet = false;
	_initialized = false;
	_mass = 0;
}

//------------------------------------------------------------------------------

Rigidbody::~Rigidbody() {
	
	if (_initialized) {
		physics::DestroyRigidbody(_body.get());
	}
}

//******************************************************************************
// Forces and impulses

void Rigidbody::ApplyForce(const Vector3 &force, bool local) {
	
	btVector3 vector = physics::ConvertVector(force);
	if (local) {
		vector = _body->getWorldTransform() * vector;
	}
	
	_body->applyCentralForce(vector);
}

//------------------------------------------------------------------------------

void Rigidbody::ApplyImpulse(const Vector3 &impulse, bool local) {

	btVector3 vector = physics::ConvertVector(impulse);
	if (local) {
		vector = _body->getWorldTransform() * vector;
	}

	_body->applyCentralImpulse(vector);
}

//------------------------------------------------------------------------------

void Rigidbody::ApplyTorque(const Vector3 &torque, bool local) {
	
	btVector3 vector = physics::ConvertVector(torque);
	if (local) {
		vector = _body->getWorldTransform() * vector;
	}
	
	_body->applyTorque(vector);
}

//------------------------------------------------------------------------------

void Rigidbody::ApplyTorqueImpulse(const Vector3 &torque, bool local) {
	
	btVector3 vector = physics::ConvertVector(torque);
	if (local) {
		vector = _body->getWorldTransform() * vector;
	}
	_body->applyTorqueImpulse(physics::ConvertVector(torque));
}

//******************************************************************************
// Setting of physics geometry

void Rigidbody::SetAsSphere(float radius) {
	
	if (_collisionShapeSet || _initialized) {
		utils::Log("Can't set as Sphere when already initialized.");
		return;
	}
	
	_collisionShape = CollisionShapePtr(new btSphereShape(radius));
	_collisionShapeSet = true;
}

//------------------------------------------------------------------------------

void Rigidbody::SetAsBox(const Vector3& halfSizes) {
	
	if (_collisionShapeSet || _initialized) {
		utils::Log("Can't set as Box. Shape is already set.");
		return;
	}
	
	btVector3 btSizes = physics::ConvertVector(halfSizes);
	_collisionShape = CollisionShapePtr(new btBoxShape(btSizes));
	_collisionShapeSet = true;
}

//------------------------------------------------------------------------------

void Rigidbody::SetAsStaticPlane(const Vector3& normal, float constant) {
	
	if (_collisionShapeSet || _initialized) {
		utils::Log("Can't set as Plane when already initialized.");
		return;
	}
	
	btVector3 btNormal = physics::ConvertVector(normal);
	_collisionShape = CollisionShapePtr(new btStaticPlaneShape(btNormal, constant));
	_collisionShapeSet = true;
}

//------------------------------------------------------------------------------

void Rigidbody::SetAsMesh(const Mesh *mesh, bool isStatic) {
	
	btTriangleMesh *data = new btTriangleMesh();
	bool isError = false;
	for (int i = 0; i < mesh->TriangleCount(); i++) {
		
		Vector3 triangle[3];
		
		for (int j = 0; j < Mesh::NUM_VERTEXES_IN_POLYGON; j++) {
			if (!mesh->GetTriangleVertex(i, j, triangle[j])) {
				isError = true;
				break;
			}
		}
		
		if (isError) break;
		
		btVector3 a = physics::ConvertVector(triangle[2]);
		btVector3 b = physics::ConvertVector(triangle[1]);
		btVector3 c = physics::ConvertVector(triangle[0]);
		
		data->addTriangle(a, b, c,false); // false, don’t remove duplicate vertices		
	}

	if (!isError) {
		_collisionShape = CollisionShapePtr(new btBvhTriangleMeshShape(data,true,true));
		_collisionShapeSet = true;
	} else {
		utils::Log("Error setting physics mesh for object " + GameObject()->Name());
	}
}

//******************************************************************************
// Component 

void Rigidbody::PreUpdate() {

	btTransform btTransform;
	_body->getMotionState()->getWorldTransform(btTransform);
	
	Quaternion rotation = physics::ConvertQuaternion(btTransform.getRotation());
	Vector3 position = physics::ConvertVector(btTransform.getOrigin());	
	
	Transform()->Rotation(rotation);
	Transform()->Position(position);
}

//------------------------------------------------------------------------------

void Rigidbody::Start() {

	// Calculate hierarchy transform matrices
	Transform()->RootParent()->CalculateTransformMatrix(true);
	Matrix4 worldMatrix = Transform()->TransformToWorldMatrix();
	
	// Getting world transform values
	Quaternion rotation = Quaternion(worldMatrix);
	Vector3 pos = math::GetTranslation(worldMatrix);

	// Converting to bullet types
	btVector3 btPosition = physics::ConvertVector(pos);
	btQuaternion btRotation = physics::ConvertQuaternion(rotation);
	btTransform transform(btRotation, btPosition);
	
	// Motion stte
	btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	_motionState = MotionStatePtr(motionState);
	
	// Inertia
	btVector3 inertia(0,0,0);
	if (_collisionShapeSet) {
		_collisionShape.get()->calculateLocalInertia(_mass,inertia);
	}
	
	// Body
	btRigidBody::btRigidBodyConstructionInfo info(_mass, motionState, _collisionShape.get(), inertia);
	_body = RigidBodyPtr(physics::CreateRigidbody(info));
	_initialized = true;
	
	// Don't rely on parent transform any more
	Transform()->ForceWorldTransform(true);
}

#endif