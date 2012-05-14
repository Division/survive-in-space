//
//  Material.cpp
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include <sstream>
#include <string>
#include "Utils.h"

static const BlendFunc blendFunctions[] = {{GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}, {GL_DST_COLOR, GL_ONE}, {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA}};

//******************************************************************************
//
//  Public
//
//******************************************************************************


Material::Material() {

	_shader = NULL;
	_texture0 = NULL;
	_texture1 = NULL;
	_hash = 0;
	_depthTest = true;
	_depthWrite = true;
	_renderQueue = RenderQueueGeometry;
	_blendFunc = blendFunctions[0];
	_blending = false;
}

void Material::SetBlendFunc(BlendFuncType type) {

	_blendFunc = blendFunctions[type];
}


void Material::SetBlendFunc(BlendFunc blendFunc) {
	
	_blendFunc = blendFunc;
}


void Material::CalculateHash() {

	std::stringstream stream;
	
	stream << _shader->Name() << "_";
	
	if (Texture()) {
		stream << Texture()->Name() << "_";
	}
	stream << _depthTest << "_";
	
	if (Texture()) {
		stream << Texture()->Name() << "_";
	}
	
	stream << _depthWrite << "_";
	
	if (Texture2()) {
		stream << Texture2()->Name() << "_";
	}
	
	stream << RenderQueue();
	
	_hash = utils::Hash(stream.str());
}