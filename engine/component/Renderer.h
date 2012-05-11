//
//  Renderer.h
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "Component.h"
#include "Render.h"

class Renderer : public Component {
public:
	
	void Material(class Material material) { _material = material; }
	class Material& Material() { return _material; }
	
protected:
	class Material _material;
	Matrix4 _worldMatrix;

	
};

#endif
