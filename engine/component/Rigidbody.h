//
//  Collider.h
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Physics.h"
#include "btBulletDynamicsCommon.h"


#ifdef ENABLE_PHYSICS

#include "Component.h"
#include <memory>
#include "MyMath.h"

typedef std::unique_ptr<btRigidBody> RigidBodyPtr;
typedef std::unique_ptr<btCollisionShape> CollisionShapePtr;
typedef std::unique_ptr<btMotionState> MotionStatePtr;

class Mesh;

class Rigidbody : public Component {
public:
	GENERATE_COMPONENT_ID(Rigidbody)

	void Start();
	
	void ApplyForce(const Vector3 &force, bool local = false);
	void ApplyImpulse(const Vector3 &impulse, bool local = false);
	void ApplyTorque(const Vector3 &torque, bool local = false);
	void ApplyTorqueImpulse(const Vector3 &torque, bool local = false);
	
	void SetAsSphere(float radius);
	void SetAsBox(const Vector3& halfSizes);
	void SetAsStaticPlane(const Vector3& normal, float constant);
	void SetAsMesh(const Mesh *mesh, bool isStatic = true);
	
	virtual void PreUpdate();
	
	void Mass(float mass) { _mass = mass; };
	float Mass() const { return _mass; }
	
	// Could return NULL!
	btRigidBody *Body() { return _body.get(); }
	
	Rigidbody();
	~Rigidbody();
	
	
private:
	CollisionShapePtr _collisionShape;
	RigidBodyPtr _body;
	MotionStatePtr _motionState;
	
	bool _collisionShapeSet;
	float _mass;
	bool _initialized;
};

#endif

#endif