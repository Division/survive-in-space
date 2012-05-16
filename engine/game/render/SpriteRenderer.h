//
//  SpriteRenderer.h
//  SurviveInSpace
//
//  Created by Nikita on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Renderer.h"
#include "Mesh.h"
#include "MyMath.h"

class SpriteRenderer : public Renderer {
public:
	GENERATE_COMPONENT_ID(SpriteRenderer)

    SpriteRenderer();
    
	//-------------------
	// Component
	virtual void Start();
    virtual void PreRender();
	virtual void Render();
	
	//-------------------
	// Default transform
	void UseTransform(bool use) { _useTransform = use; }
	bool UseTransform() const { return _useTransform; }
	
	//-------------------
	// Custom transform
	void Size(Vector2 size) { _size = size; }
	Vector2 Size() const { return _size; } 
	void Position(Vector2 position) { _position = position; }
	Vector2 Position() const { return _position; } 
	void Rotation(float rotation) { _rotation = rotation; }
	float Rotation() const { return _rotation; } 

	//-------------------
	// UV
    Vector2 UVOffset() const { return _uvOffset; }
    void UVOffset(Vector2 offset) { _uvOffset = offset; _needGenerateUV = true; }

    Vector2 UVScale() const { return _uvScale; }
    void UVScale(Vector2 scale) { _uvScale = scale; _needGenerateUV = true; }

    
private:
	void GenerateMesh(Mesh *mesh);
	void GenerateUV();
    
private:
	MeshPtr _mesh;
	bool _useTransform;
	Vector2 _size;
	Vector2 _position;
	float _rotation;
    Vector2 _uvScale;
    Vector2 _uvOffset;
    bool _needGenerateUV;
    Vector2 _currentUV[4];
};

#endif