//
//  SpriteRenderer.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "SpriteRenderer.h"
#include "GameObject.h"
#include "RenderPipeline.h"
#include "Render.h"
#include "Transform.h"

//******************************************************************************
//
//  Public
//
//******************************************************************************


//******************************************************************************
// Component

void SpriteRenderer::Start() {
	
	_mesh = MeshPtr(new Mesh());
	GenerateMesh(_mesh.get());
}

//------------------------------------------------------------------------------

void SpriteRenderer::Render() {
	
	RenderPipeline *pipeline = GameObject()->RenderPipeline();
	
	RenderOperation rop;
	rop.material = &_material;
	rop.mesh = _mesh.get();
	
	Matrix4 scale = math::Scaling(Vector3(_size, 1));
	
	if (_useTransform) {
		_worldMatrix = Transform()->TransformToWorldMatrix();
	} else {
		Quaternion rotation = math::Rotation(_rotation, Vector3(0,0,1));
		Matrix4 transform = Transform::GetRTMatrix(Vector3(_position, 0), rotation);
		_worldMatrix = transform;
	}
	
	_worldMatrix *= scale;
	
	rop.worldMatrix = &_worldMatrix;
	rop.is2D = true;
	pipeline->AddRenderOperation(rop);
}

//******************************************************************************
//
//  Private
//
//******************************************************************************

void SpriteRenderer::GenerateMesh(Mesh *mesh) {

	float halfSize = 0.5;
	Vector3 vertices[4] = {Vector3(-halfSize, -halfSize,0), Vector3(-halfSize, halfSize,0), Vector3(halfSize, halfSize,0), Vector3(halfSize, -halfSize,0)};
	Vector2 uv0[4] = {Vector2(0,0), Vector2(0,1), Vector2(1,1), Vector2(1,0)};
	unsigned short indexes[6] = {0,1,2,2,3,0};
	
	mesh->SetRenderData(vertices, 4, indexes, 2);
	mesh->SetUV0(uv0);
}