//
//  RenderState.h
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef RENDER_STATE_H
#define RENDER_STATE_H

#include "RenderPipeline.h"
#include "Render.h"
#include "Shader.h"

class Camera;

class RenderState {
public:
	
	const void* ApplyStateForROP(RenderOperation &renderOp, Camera *camera);
	void RecoverState();
	
private:
	bool _currentBlendEnabled;
	Mesh *_currentMesh;
	Shader *_currentShader;
	Texture *_currentTexture0;
	Texture *_currentTexture1;
	char _vertexAttribEnabled[EngineShaderAttributesCount];
	const void *_currentIndexPointer;
	
};

#endif
