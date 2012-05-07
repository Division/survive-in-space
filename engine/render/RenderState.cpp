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

const void* RenderState::ApplyStateForROP(RenderOperation &renderOp, Camera *camera) {

	// Shader
	if (renderOp.material->Shader() != _currentShader) {
		_currentShader = renderOp.material->Shader();
		_currentShader->Use();
		_currentShader->SetUniform(EngineShaderParamProjectionMatrixUniform, camera->ProjectionMatrix());
	}
	
	// Texture 0
	if (_currentTexture0 != renderOp.material->Texture()) {
		_currentTexture0 = renderOp.material->Texture();
		if (_currentTexture0) {
			_currentTexture0->Bind(_currentShader->GetShaderParameter(EngineShaderParamTexture0Uniform));
		} else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	
	// Texture 1
	if (_currentTexture1 != renderOp.material->Texture2()) {
		_currentTexture1 = renderOp.material->Texture2();
		if (_currentTexture1) {
			_currentTexture1->Bind(_currentShader->GetShaderParameter(EngineShaderParamTexture1Uniform));
		} else {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);	
		}
	}
	
	const void *indexPointer = _currentIndexPointer;
	const char *vertexPointer;
	
	if (_currentMesh != renderOp.mesh) {

		_currentMesh = renderOp.mesh;
		
		// TODO: add check and disabling of vertex attribs
		
		// Pos attrib
		int attrib;
		attrib = _currentShader->GetShaderParameter(EngineShaderParamPositionAttribute);
		if (!_vertexAttribEnabled[attrib]) {
			_vertexAttribEnabled[attrib] = 1;
			glEnableVertexAttribArray(attrib);
		}

		// Texcoord attrib
		attrib = _currentShader->GetShaderParameter(EngineShaderParamUV0Attribute);
		if (!_vertexAttribEnabled[attrib]) {
			_vertexAttribEnabled[attrib] = 1;
			glEnableVertexAttribArray(attrib);
		}
		
		if (_currentMesh->UsesVBO()) {
			indexPointer = 0;
			vertexPointer = 0;
			glBindBuffer(GL_ARRAY_BUFFER, _currentMesh->GetVertexBuffer());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _currentMesh->GetIndexBuffer());
		} else {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			indexPointer = _currentMesh->IndexDataPointer();
			vertexPointer = _currentMesh->VertexDataPointer();
		}
		
		int stride = Mesh::VERTEX_STRIDE*sizeof(float) + Mesh::UV_STRIDE*sizeof(float);
		
		glVertexAttribPointer(_currentShader->GetShaderParameter(EngineShaderParamPositionAttribute), Mesh::VERTEX_STRIDE, GL_FLOAT, GL_FALSE, stride, vertexPointer);
		glVertexAttribPointer(_currentShader->GetShaderParameter(EngineShaderParamUV0Attribute), Mesh::UV_STRIDE, GL_FLOAT, GL_FALSE, stride, vertexPointer + Mesh::VERTEX_STRIDE*sizeof(float));
		
		_currentIndexPointer = indexPointer;
	}

	return indexPointer;
}


void RenderState::RecoverState() {

	if (_currentMesh) {
		if (_currentMesh->UsesVBO()) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	_currentMesh = NULL;
	
	for (int i = 0; i < 8; i++) {
		if (_vertexAttribEnabled[i]) {
			_vertexAttribEnabled[i] = 0;
			glDisableVertexAttribArray(i);
		}
	}
	
	if (_currentShader) {
		_currentShader = 0;
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

	glActiveTexture(GL_TEXTURE1);
}