//
//  RenderPipeline.cpp
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "RenderPipeline.h"
#include "Camera.h"
#include "Transform.h"
#include "RenderState.h"

RenderPipeline::RenderPipeline(RenderState* renderState) {
	
	_renderState = renderState;
}

//******************************************************************************
// Render preparation

void RenderPipeline::PreparePipeline(int estimatedObjCount, Camera *camera) {

	_renderOperationList.resize(0);
	if (_renderOperationList.capacity() < estimatedObjCount) {
		_renderOperationList.reserve(estimatedObjCount);
	}
	
	_currentCamera = camera;
}

//------------------------------------------------------------------------------

void RenderPipeline::AddRenderOperation(RenderOperation &operation) {

	operation.discarded = false;
	Vector3 pos = math::GetTranslation(*operation.worldMatrix);
	Vector3 cameraPos = _currentCamera->Transform()->Position();
	operation.sqareDistanceToCamera = pos.x * cameraPos.x + pos.y * cameraPos.y + pos.z * cameraPos.z;
	
	_renderOperationList.push_back(operation);
}

//******************************************************************************
// Rendering configuration

void RenderPipeline::Render() {

	// Sorting by render queue
	std::sort(_renderOperationList.begin(), _renderOperationList.end(), SortOnRenderQueue);
	// todo: add transparent objects handling [sort by distance for their part of array]
	
	for (RenderOperationList::iterator it = _renderOperationList.begin(); it != _renderOperationList.end(); it++) {
		ProcessRender(*it);
	}
	
	_renderState->RecoverState();
}

//******************************************************************************
// Sorting

bool RenderPipeline::SortOnRenderQueue(RenderOperation &operationA, RenderOperation &operationB) {

	return operationA.material->RenderQueue() < operationB.material->RenderQueue();
}


//******************************************************************************
// Process of rendering

void RenderPipeline::ProcessRender(RenderOperation &renderOp) {

	const void *indexPointer;
	indexPointer = _renderState->ApplyStateForROP(renderOp, _currentCamera);
	
	// Setting modelview matrix
    Matrix4 model = _currentCamera->WorldMatrix() * (*renderOp.worldMatrix);
    renderOp.material->Shader()->SetUniform(EngineShaderParamModelViewMatrixUniform, model);
	
	glDrawElements(GL_TRIANGLES, renderOp.mesh->TriangleCount() * Mesh::NUM_VERTEXES_IN_POLYGON, GL_UNSIGNED_SHORT, indexPointer);
}

