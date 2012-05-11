//
//  MeshRenderer.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ComponentDeclaration.h"
#include "Transform.h"
#include "RenderPipeline.h"
#include "GameObject.h"

void MeshRenderer::Render() {
	
	if (!_mesh) return;
	if (!_mesh->IsValid()) return;
	Shader *shader = _material.Shader();
	if (!shader) return;

	RenderPipeline *pipeline = GameObject()->RenderPipeline();
	
	RenderOperation rop;
	rop.material = &_material;
	rop.mesh = _mesh;
	rop.is2D = false;
	_worldMatrix = Transform()->TransformToWorldMatrix();
	rop.worldMatrix = &_worldMatrix;
	pipeline->AddRenderOperation(rop);
}