//
//  Physics.cpp
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Physics.h"
#include "Render.h"
#include "Camera.h"
#include "Shader.h"
#include "GameObject.h"
#include "Scene.h"

namespace physics {

	static btBroadphaseInterface* broadPhase;
	static btDefaultCollisionConfiguration* collisionConfiguration;
	static btCollisionDispatcher* dispatcher;
	static btSequentialImpulseConstraintSolver* solver;
	static btDiscreteDynamicsWorld* world;
	static IPhysicsCallbackReceiver *callbackReceiver;
	
	
	void PhysicsTickCallback(btDynamicsWorld *world, btScalar timeStep);
	
	void Init(IPhysicsCallbackReceiver *receiver) {
		
		callbackReceiver = receiver;
		
		// Build the broadphase
		broadPhase = new btDbvtBroadphase();
		
		// Set up the collision configuration and dispatcher
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		
		// The actual physics solver
		solver = new btSequentialImpulseConstraintSolver;
		
		// The world.
		world = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);
		world->setGravity(btVector3(0,0,0));
		world->setInternalTickCallback(PhysicsTickCallback);
		
		#ifdef ENABLE_DEBUG_DRAW
		DebugDrawer *drawer = new DebugDrawer;
		drawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		world->setDebugDrawer(drawer);
		#endif
	}
	
	void PhysicsTickCallback(btDynamicsWorld *world, btScalar timeStep) {
		
		world->clearForces();
		if (callbackReceiver) {
			callbackReceiver->PhysicsTickCallback(timeStep);
		}
	}
			
	
	void Update() {
		
		world->clearForces();
		world->stepSimulation(utils::DeltaTime(), 5, 1.0f/60.0f);
	}
	
	
	void Render() {
		
		#ifdef ENABLE_DEBUG_DRAW
		world->debugDrawWorld();
		#endif
	}
	
	
	void AddRigidbody(btRigidBody *body) {
		
		world->addRigidBody(body);
	}
	
	btRigidBody* CreateRigidbody(btRigidBody::btRigidBodyConstructionInfo &info) {
		
		btRigidBody* body = new btRigidBody(info);
		world->addRigidBody(body);
		return body;
	}
	
	
	void DestroyRigidbody(btRigidBody *body) {
		
		world->removeRigidBody(body);
	}
	
	
	btVector3 ConvertVector(const Vector3 &vector) {
		
		return btVector3(vector.x, vector.y,vector.z);
	}

	
	Vector3 ConvertVector(const btVector3 &vector) {
		
		return Vector3(vector.x(),vector.y(),vector.z());
	}
	
	
	Quaternion ConvertQuaternion(const btQuaternion &quat) {

		return Quaternion(quat.w(),quat.x(),quat.y(),quat.z());
	}
	
	
	btQuaternion ConvertQuaternion(const Quaternion &quat) {

		return btQuaternion(quat.x,quat.y,quat.z,quat.w);
	}
	
	btMatrix3x3 ConvertMatrix(const Matrix4 &m) {

		
		Matrix3 mat3(glm::transpose(m));
		btMatrix3x3 result = *(btMatrix3x3*)&mat3;
		return result;
	}
	
	
	Matrix4 ConvertMatrix(const btMatrix3x3&m) {
		
		btMatrix3x3 transpose = m.transpose();
		Matrix3 mat3 = *(Matrix3*)(&transpose);
		mat3 = glm::transpose(mat3);
		Matrix4 result(mat3);
		return result;
	}
	
	
	void ConfigureAsCollisionGeometry(GameObject *object, bool recursive, bool disableRenderer) {
		
		if (object->Renderer()) {
			
			Rigidbody *r = object->Rigidbody();

			if (!object->Rigidbody()) {
				object->AddComponent<Rigidbody>();
			}
			
			r = object->Rigidbody();
			
			object->Rigidbody()->SetAsMesh(object->Renderer()->Mesh());
			object->Rigidbody()->Mass(0);

			if (disableRenderer) {
				object->Renderer()->Active(false);
			}
		}
		
		if (recursive) {
			Transform *t = object->Transform();
			for (TransformList::const_iterator it = t->Children().begin(); it != t->Children().end(); it++) {
				ConfigureAsCollisionGeometry((*it)->GameObject(), recursive, disableRenderer);
			}
		}
	}
	
	#ifdef ENABLE_DEBUG_DRAW
	DebugDrawer::DebugDrawer() { 
		
		_shader = resource::GetShader("SimpleColor"); 
	}
	
	
	void DebugDrawer::drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color) {
        
		if (!_shader) return;
		
		_shader->Use();
		
        // Set the projection matrix
		Matrix4 model = Camera::Main()->WorldMatrix();
		Matrix4 proj = Camera::Main()->ProjectionMatrix();
		
		_shader->SetUniform("Modelview", model);
		_shader->SetUniform("Projection", proj);
		
		// Vertex attributes
		
//		glEnableVertexAttribArray(_shader->Attribute("Position"));
		glEnableVertexAttribArray(0);
		glDisableVertexAttribArray(1);		
		
        // Set the colour of the line
        Vector4 v = Vector4(color.getX(), color.getY(), color.getZ(), 1);
        _shader->SetUniform("Color", v);
		
        // Set the line vertices
        float tmp[ 6 ] = { from.getX(), from.getY(), from.getZ(),
            to.getX(), to.getY(), to.getZ() };

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, &tmp[0]);
        glDrawArrays( GL_LINES, 0, 2 );
		
		glDisableVertexAttribArray(0);
	}
	#endif


}