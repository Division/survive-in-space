//
//  Material.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Shader;
class Texture;

typedef enum {
	RenderQueueBackground = 1000,
	RenderQueueGeometry = 2000,
	RenderQueueTransparent = 3000,
	RenderQueueOverlay = 4000
} RenderQueue;

class Material {
public:
	Material();
	
	void Shader(class Shader *shader) { _shader = shader; if (_hash) CalculateHash(); }
	class Shader *Shader() const { return _shader; }
	
	void Texture(class Texture *texture) { _texture0 = texture; if (_hash) CalculateHash(); }
	class Texture *Texture() const { return _texture0; }

	void Texture2(class Texture *texture) { _texture1 = texture; if (_hash) CalculateHash(); }
	class Texture *Texture2() const { return _texture1; }
	
	void RenderQueue(int queue) { _renderQueue = queue; if (_hash) CalculateHash(); }
	int RenderQueue() { return _renderQueue; }
	
	void CalculateHash();
	
private:
	class Shader *_shader;
	class Texture *_texture0;
	class Texture *_texture1;
	int _renderQueue;
	int _hash;
};

#endif
