//
//  Physics.h
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PHYSICS_H
#define PHYSICS_H

// Comment this to disable physics support
#define ENABLE_PHYSICS
#ifdef ENABLE_PHYSICS

//#define ENABLE_DEBUG_DRAW

#include "btBulletDynamicsCommon.h"
#include "MyMath.h"

class Shader;
class GameObject;

namespace physics {

	class IPhysicsCallbackReceiver {
	public:
		virtual void PhysicsTickCallback(float timeStep) = 0;
	};
	
	#ifdef ENABLE_DEBUG_DRAW
	class DebugDrawer : public btIDebugDraw {
	public:
		DebugDrawer();
		virtual void drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color);
		virtual void drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) {}
		virtual void reportErrorWarning (const char *warningString) {}
		virtual void draw3dText (const btVector3 &location, const char *textString) {}
		virtual void setDebugMode (int debugMode) { _mode = debugMode; }
		virtual int getDebugMode () const { return _mode; }
		
	private:
		int _mode;
		Shader *_shader;
	};
	#endif
	
	void Init(IPhysicsCallbackReceiver *receiver);
	void Render(); // Debug
	void Update();
	
	void ConfigureAsCollisionGeometry(GameObject *object, bool recursive, bool disableRenderer = true);
	
	btRigidBody* CreateRigidbody(btRigidBody::btRigidBodyConstructionInfo &info);
	void AddRigidbody(btRigidBody *body);
	void DestroyRigidbody(btRigidBody *body);
	
	btVector3 ConvertVector(const Vector3 &vector);
	Vector3 ConvertVector(const btVector3 &vector);
	Quaternion ConvertQuaternion(const btQuaternion &quat);
	btQuaternion ConvertQuaternion(const Quaternion &quat);	
	btMatrix3x3 ConvertMatrix(const Matrix4 &m);
	Matrix4 ConvertMatrix(const btMatrix3x3 &m);
	
	
}




#endif

#endif