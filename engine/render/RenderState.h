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
#include "MyMath.h"

class Camera;
class Mesh;

class RenderState {
public:
	
	const void* ApplyStateForROP(RenderOperation &renderOp, Matrix4 *projection);
	void RecoverState();
	
private:
	void EnableAttributes(Mesh *mesh, Shader *shader);
	void DisableAttributes();
	void SetupAttributesVBO(Mesh *mesh, Shader *shader);
	void SetupAttributesNoVBO(Mesh *mesh, Shader *shader);
	
private:
	bool _currentBlendEnabled;
	Mesh *_currentMesh;
	Shader *_currentShader;
	Texture *_currentTexture0;
	Texture *_currentTexture1;
	char _vertexAttribEnabled[EngineShaderAttributesCount];
	const void *_currentIndexPointer;
	Matrix4 *_currentProjection;
	bool _currentDepthWrite;
	bool _currentDepthTest;
	bool _currentBlending;
};

#endif
