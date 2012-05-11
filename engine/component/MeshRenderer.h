//
//  MeshRenderer.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Renderer.h"
#include "MyMath.h"

class MeshRenderer : public Renderer {
public:
	GENERATE_COMPONENT_ID(MeshRenderer)
	
	void Mesh(class Mesh *mesh) { _mesh = mesh; }
	class Mesh *Mesh(void) const { return _mesh; }
	
	virtual void Render();
		
private:
	class Mesh *_mesh;
	
};

#endif
