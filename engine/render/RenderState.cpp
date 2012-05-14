//
//  RenderState.cpp
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RenderState.h"
#include "Camera.h"

//******************************************************************************
//
//  Public
//
//******************************************************************************


const void* RenderState::ApplyStateForROP(RenderOperation &renderOp, Matrix4 *projection) {

	// TODO: Check if shader params correct change
	
	if (renderOp.material->Blending() ^ _currentBlending) {
		_currentBlending = renderOp.material->Blending();
		if (_currentBlending) {
			glEnable(GL_BLEND);
			glBlendFunc(renderOp.material->SourceFactor(), renderOp.material->DestFactor());
		} else {
			glDisable(GL_BLEND);
		}
	}
	
	if (renderOp.material->DepthTest() ^ _currentDepthTest) {
		_currentDepthTest = renderOp.material->DepthTest();
		if (_currentDepthTest) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}
	
	if (renderOp.material->DepthWrite() ^ _currentDepthWrite) {
		_currentDepthWrite = renderOp.material->DepthWrite();
		glDepthMask(_currentDepthWrite);
	}
	
	// Shader and projection
	bool shaderChanged = false;
	if (renderOp.material->Shader() != _currentShader) {
		shaderChanged = true;
		_currentShader = renderOp.material->Shader();
		_currentShader->Use();
		_currentProjection = projection;
	}
	
	_currentShader->SetUniform(EngineShaderParamProjectionMatrixUniform, *projection);
	
	// Texture 0
	if (shaderChanged || _currentTexture0 != renderOp.material->Texture()) {
		_currentTexture0 = renderOp.material->Texture();
		if (_currentTexture0) {
			_currentTexture0->Bind(0);
		} else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		_currentShader->SetUniform(EngineShaderParamTexture0Uniform, 0);
	}
	
	// Texture 1
	if (shaderChanged || _currentTexture1 != renderOp.material->Texture2()) {
		_currentTexture1 = renderOp.material->Texture2();
		if (_currentTexture1) {
			_currentTexture1->Bind(_currentShader->GetShaderParameter(EngineShaderParamTexture1Uniform));
		} else {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);	
		}
		_currentShader->SetUniform(EngineShaderParamTexture1Uniform, 1);
	}
	
	const void *indexPointer = _currentIndexPointer;
	
	if (_currentMesh != renderOp.mesh) {

		_currentMesh = renderOp.mesh;
		
		DisableAttributes();
		EnableAttributes(_currentMesh, _currentShader);
		
		if (_currentMesh->UsesVBO()) { // Use VBO
			indexPointer = 0;
			SetupAttributesVBO(_currentMesh, _currentShader);
		} else { // No VBO
			indexPointer = _currentMesh->GetIndexDataPointer();
			SetupAttributesNoVBO(_currentMesh, _currentShader);
		}
		
		_currentIndexPointer = indexPointer;
	}

	return indexPointer;
}

//------------------------------------------------------------------------------

void RenderState::RecoverState() {

	_currentProjection = NULL;
	
	if (_currentBlending) {
		glDisable(GL_BLEND);
		_currentBlending = false;
	}
	
	if (_currentMesh) {
		if (_currentMesh->UsesVBO()) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	_currentMesh = NULL;
	
	DisableAttributes();
	
	if (_currentShader) {
		_currentShader = NULL;
		glUseProgram(0);
	}
	
	if (_currentTexture0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	if (_currentTexture1) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(GL_TEXTURE0);
	
	_currentTexture0 = NULL;
	_currentTexture1 = NULL;
	
	if (!_currentDepthTest) {
		_currentDepthTest = true;
		glEnable(GL_DEPTH_TEST);
	}
	
	if (!_currentDepthWrite) {
		_currentDepthWrite = true;
		glDepthMask(true);
	}
}

//******************************************************************************
//
//  Private
//
//******************************************************************************


void RenderState::SetupAttributesVBO(Mesh *mesh, Shader *shader) {
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _currentMesh->GetIndexBuffer());
	
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexBuffer());
	int vertexAttribIndex = shader->GetShaderParameter(EngineShaderParamPositionAttribute);
	glVertexAttribPointer(vertexAttribIndex, Mesh::VERTEX_STRIDE, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Normals
	bool needNormals = mesh->HasNormals() && shader->ShaderUsesParameter(EngineShaderParamNormalAttribute);
	if (needNormals) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexBuffer());
		int normalAttribIndex = shader->GetShaderParameter(EngineShaderParamNormalAttribute);
		glVertexAttribPointer(normalAttribIndex, Mesh::NORMAL_STRIDE, GL_FLOAT, GL_FALSE, 0, 0);
	}
	
	// UV0
	bool needUV0 = mesh->HasUV0() && shader->ShaderUsesParameter(EngineShaderParamUV0Attribute);
	if (needUV0) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->GetUV0Buffer());
		int uv0AttribIndex = shader->GetShaderParameter(EngineShaderParamUV0Attribute);
		glVertexAttribPointer(uv0AttribIndex, Mesh::UV_STRIDE, GL_FLOAT, GL_FALSE, 0, 0);				
	}
	
	// UV1
	bool needUV1 = mesh->HasUV1() && shader->ShaderUsesParameter(EngineShaderParamUV1Attribute);
	if (needUV1) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->GetUV1Buffer());
		int uv1AttribIndex = shader->GetShaderParameter(EngineShaderParamUV1Attribute);
		glVertexAttribPointer(uv1AttribIndex, Mesh::UV_STRIDE, GL_FLOAT, GL_FALSE, 0, 0);				
	}

}

//------------------------------------------------------------------------------

void RenderState::SetupAttributesNoVBO(Mesh *mesh, Shader *shader) {
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// Vertices
	const char *vertexData = mesh->GetVertexDataPointer();
	int vertexAttribIndex = shader->GetShaderParameter(EngineShaderParamPositionAttribute);
	glVertexAttribPointer(vertexAttribIndex, Mesh::VERTEX_STRIDE, GL_FLOAT, GL_FALSE, 0, vertexData);
	
	// Normals
	bool needNormals = mesh->HasNormals() && shader->ShaderUsesParameter(EngineShaderParamNormalAttribute);
	if (needNormals) {
		const char *normalData = mesh->GetNormalDataPointer();
		int normalAttribIndex = shader->GetShaderParameter(EngineShaderParamNormalAttribute);
		glVertexAttribPointer(normalAttribIndex, Mesh::NORMAL_STRIDE, GL_FLOAT, GL_FALSE, 0, normalData);
	}
	
	// UV0
	bool needUV0 = mesh->HasUV0() && shader->ShaderUsesParameter(EngineShaderParamUV0Attribute);
	if (needUV0) {
		const char *uv0Data = mesh->GetUV0DataPointer();
		int uv0AttribIndex = shader->GetShaderParameter(EngineShaderParamUV0Attribute);
		glVertexAttribPointer(uv0AttribIndex, Mesh::UV_STRIDE, GL_FLOAT, GL_FALSE, 0, uv0Data);
	}
	
	// UV1
	bool needUV1 = mesh->HasUV1() && shader->ShaderUsesParameter(EngineShaderParamUV1Attribute);
	if (needUV1) {
		const char *uv1Data = mesh->GetUV1DataPointer();
		int uv1AttribIndex = shader->GetShaderParameter(EngineShaderParamUV1Attribute);
		glVertexAttribPointer(uv1AttribIndex, Mesh::UV_STRIDE, GL_FLOAT, GL_FALSE, 0, uv1Data);
	}
}

//------------------------------------------------------------------------------

void RenderState::EnableAttributes(Mesh *mesh, Shader *shader){

	for (int i = 0; i < EngineShaderAttributesCount; i++) {
		bool enabled = shader->ShaderUsesParameter(i);
		if (!enabled) continue;
		
		int attribIndex = shader->GetShaderParameter(i);
		glEnableVertexAttribArray(attribIndex);
		_vertexAttribEnabled[attribIndex] = 1;
	}
	
}

//------------------------------------------------------------------------------

void RenderState::DisableAttributes() {

	for (int i = 0; i < EngineShaderAttributesCount; i++) {
		if (_vertexAttribEnabled[i]) {
			glDisableVertexAttribArray(i);
			_vertexAttribEnabled[i] = 0;
		}
	}
}

