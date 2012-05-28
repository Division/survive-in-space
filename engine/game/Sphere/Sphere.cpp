//
//  Sphere.cpp
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Sphere.h"
#include "Transform.h"
#include "Material.h"
#include "GameObject.h"
#include "Spawn.h"
#include "CreationUtility.h"

//******************************************************************************
//
//  Public
//
//******************************************************************************

//******************************************************************************
// Component

void Sphere::Awake() {

	Transform()->Position(Vector3(0,0,0));
	
	class Transform *geom = Transform()->Find("Geometry");
	if (geom) {
		_sphereGeometry = geom->GameObject();
		
		Material material;
		material.Texture(resource::GetTexture("lightmap_brighter.pvr"));
		material.Shader(resource::GetShader("SimpleShader"));
		_sphereGeometry->SetMaterial(material);
		physics::ConfigureAsCollisionGeometry(_sphereGeometry, true, false);
	}
	
	_triangles = Transform()->Find("SpawnTriangles");
	_triangles->Position(Vector3(0,0,0));
	
	Transform()->CalculateTransformMatrix(true);
	
	if (_triangles) {
		_triangles->GameObject()->SetActiveRecursively(false);
		InitSpawns();
	}
	


}

//******************************************************************************
//
//  Private
//
//******************************************************************************

void Sphere::CreateSpawn(const class Transform *transform) {

	const Matrix4 m = transform->TransformToWorldMatrix();
	Matrix3 rotation = Matrix3(m);
	
	Vector3 position = transform->Position();
	MeshRenderer *renderer = transform->GameObject()->GetComponent<MeshRenderer>();
	Mesh *mesh = renderer->Mesh();
	
	Vector3 average = Vector3(0);
	Vector3 normal;
	mesh->GetTriangleNormal(0, 0, normal);
	
	Vector3 vertices[3];
	
	for (int i = 0; i < 3; i++) {
		Vector3 vertex;
		mesh->GetTriangleVertex(0, i, vertex);
		average += vertex;
		vertices[i] = Vector3(m * Vector4(vertex, 0));
	}
	
	average /= 3.0f;
	
	average = Vector3(m * Vector4(average, 0));
//	normal = normal * rotation;
	normal =  math::Normalize(math::Cross(vertices[2] - vertices[1], vertices[2] - vertices[0]));
//	normal = math::Normalize(Transform()->Position() + _sphereGeometry->Transform()->Position() - average);
	Spawn *spawn = creation::CreateSpawn(NULL);
	spawn->Transform()->Position(average);
	spawn->Transform()->Rotation(math::Rotation(45, normal));
	
	_spawns.push_back(spawn);
}

//------------------------------------------------------------------------------

void Sphere::InitSpawns() {

	const TransformList &spawnTransforms = _triangles->Children();
	for (TransformList::const_iterator it = spawnTransforms.begin(); it != spawnTransforms.end(); it++) {
		CreateSpawn(*it);
	}
	
	for (int i = 0; i < _spawns.size(); i++) {
		class GameObject *spawnObject = _spawns[i]->GameObject();
		spawnObject->SetActiveRecursively(i % 30 == 0);
	}
}
