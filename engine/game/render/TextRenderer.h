//
//  TextRenderer.h
//  SurviveInSpace
//
//  Created by Nikita on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Renderer.h"
#include "Mesh.h"
#include <string>

class Font;

class TextRenderer: public Renderer {
public:
	GENERATE_COMPONENT_ID(TextRenderer)
	
	TextRenderer();
	
	//-------------------
	// Component
	virtual void Start();
	virtual void Render();
	
	//-------------------
	// Properties
	void Position(Vector2 position) { _position = position; }
	Vector2 Position() const { return _position; }
	
	void Font(class Font *font);
	class Font *Font() const { return _font; }
	
	void Is3D(bool is3D);
	bool Is3D() const { return _is3D; } 
	
	const std::string &Text() const { return _text; }
	void Text(const std::string &text);
	
	void CharacterSize(float size) { _characterSize = size; }
	float CharacterSize() const { return _characterSize; }

	void LetterSpacing(float spacing) { _letterSpacing = spacing; }
	float LetterSpacing() const { return _letterSpacing; }

	
private:
	void GenerateMesh(Mesh *mesh, class Font *font, const std::string &text);
	
private:
	std::string _text;
	MeshPtr _textMesh;
	Vector2 _position;
	bool _is3D;
	float _characterSize;
	float _letterSpacing;
	class Font *_font;
};


#endif
