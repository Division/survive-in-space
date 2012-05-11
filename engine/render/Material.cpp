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

Material::Material() {

	_shader = NULL;
	_texture0 = NULL;
	_texture1 = NULL;
	_hash = 0;
	_depthTest = true;
	_depthWrite = true;
	_renderQueue = RenderQueueGeometry;
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