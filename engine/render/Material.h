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

typedef enum {
	BlendFuncTransparent = 0,
	BlendFuncAdditive,
	BlendFuncMultiply,
	BlendFuncCount
} BlendFuncType;

typedef struct {
	int sourceFactor;
	int destFactor;
} BlendFunc;


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
	
	void DepthTest(bool enable) { _depthTest = enable; if (_hash) CalculateHash(); }
	bool DepthTest() { return _depthTest; }

	void DepthWrite(bool enable) { _depthWrite = enable; if (_hash) CalculateHash(); }
	bool DepthWrite() { return _depthWrite; }
	
	void Blending(bool enabled) { _blending = enabled; }
	bool Blending() const { return _blending; }
	
	void SetBlendFunc(BlendFuncType type);
	void SetBlendFunc(BlendFunc blendFunc);
	
	int SourceFactor() { return _blendFunc.sourceFactor; }
	int DestFactor() { return _blendFunc.destFactor; }
	
	void CalculateHash();
	
private:
	class Shader *_shader;
	class Texture *_texture0;
	class Texture *_texture1;
	bool _depthTest;
	bool _depthWrite;
	int _renderQueue;
	int _hash;
	bool _blending;
	BlendFunc _blendFunc;
};

#endif
