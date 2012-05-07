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

	//
	RenderPipeline *pipeline = GameObject()->RenderPipeline();
	
	RenderOperation rop;
	rop.material = &_material;
	rop.mesh = _mesh;
	_worldMatrix = Transform()->TransformToWorldMatrix();
	rop.worldMatrix = &_worldMatrix;
	pipeline->AddRenderOperation(rop);
	////
	
/*	
	// Setting shader
	shader->Use();
	
	// Textures
	
	if (_material.Texture()) {
		_material.Texture()->Bind(0);
		shader->SetUniform("Texture", 0);
	}

	if (_material.Texture2()) {
		_material.Texture2()->Bind(1);
		shader->SetUniform("Texture2", 1);
	}
	
	// Matrix uniforms
	
    Matrix4 model = Camera::Main()->WorldMatrix() * Transform()->TransformToWorldMatrix();
    Matrix4 proj = Camera::Main()->ProjectionMatrix();
    
    shader->SetUniform("Modelview", model);
    shader->SetUniform("Projection", proj);
    
	// Vertex attributes
	
    glEnableVertexAttribArray(shader->Attribute("Position"));
    glEnableVertexAttribArray(shader->Attribute("Texcoord"));
	
	const void *indexPointer;
	const char *vertexPointer;
	if (_mesh->UsesVBO()) {
		indexPointer = 0;
		vertexPointer = 0;
		
		glBindBuffer(GL_ARRAY_BUFFER, _mesh->GetVertexBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->GetIndexBuffer());
	} else {
		indexPointer = _mesh->IndexDataPointer();
		vertexPointer = _mesh->VertexDataPointer();
	}
	
	int stride = Mesh::VERTEX_STRIDE*sizeof(float) + Mesh::UV_STRIDE*sizeof(float);
	
	glVertexAttribPointer(shader->Attribute("Position"), Mesh::VERTEX_STRIDE, GL_FLOAT, GL_FALSE, stride, vertexPointer);
	glVertexAttribPointer(shader->Attribute("Texcoord"), Mesh::UV_STRIDE, GL_FLOAT, GL_FALSE, stride, vertexPointer + Mesh::VERTEX_STRIDE*sizeof(float));
	
	// Render
	
    glDrawElements(GL_TRIANGLES, _mesh->TriangleCount() * Mesh::NUM_VERTEXES_IN_POLYGON, GL_UNSIGNED_SHORT, indexPointer);

	// Recover
	if (_material.Texture2()) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	if (_material.Texture()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	if (_mesh->UsesVBO()) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
	}
	
	glDisableVertexAttribArray(shader->Attribute("Position"));
    glDisableVertexAttribArray(shader->Attribute("Texcoord"));
	
	glUseProgram(0);*/

}