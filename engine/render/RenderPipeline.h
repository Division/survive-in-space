//
//  RenderPipeline.h
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef RENDER_PIPELINE_H
#define RENDER_PIPELINE_H

#include "Render.h"
#include <vector>
#include "MyMath.h"

class Camera;
class RenderState;

typedef struct {
	
	Mesh *mesh;
	Material *material;
	Matrix4 *worldMatrix;
	bool discarded;
	bool is2D; // Hack for rendering with ortho projection
	float sqareDistanceToCamera;
	
} RenderOperation;

typedef std::vector<RenderOperation> RenderOperationList;

class RenderPipeline {
public:	

	RenderPipeline(RenderState* renderState);
	
	void PreparePipeline(int estimatedObjCount, Camera *camera);
	void AddRenderOperation(RenderOperation &operation);
	void Render();
	
private:
	static bool SortOnRenderQueue(RenderOperation &operationA, RenderOperation &operationB);
	void ProcessRender(RenderOperation &renderOp);

private:
	RenderOperationList _renderOperationList;
	Camera *_currentCamera;
	RenderState *_renderState;
	int _transparentFirstIndex;
	int _transparentLastIndex;
};

#endif
