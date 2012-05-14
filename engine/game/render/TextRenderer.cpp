//
//  TextRenderer.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "TextRenderer.h"
#include "RenderPipeline.h"
#include "GameObject.h"
#include "Font.h"
#include "Utils.h"

//******************************************************************************
//
//  Public
//
//******************************************************************************

//******************************************************************************
// Construct/destruct

TextRenderer::TextRenderer() {
	
	_is3D = false;
	_position = Vector2(0, 0);
	_textMesh = MeshPtr(new Mesh());
	_characterSize = 5;
	_letterSpacing = 1;
	_font = NULL;
}

//******************************************************************************
// Component

void TextRenderer::Start() {
	
}

//------------------------------------------------------------------------------

void TextRenderer::Render() {
	
	if (!_textMesh) return;
	if (!_textMesh->IsValid()) return;
	Shader *shader = _material.Shader();
	if (!shader) return;
	if (!shader->Valid()) return;
	
	RenderOperation rop;
	rop.material = &_material;
	rop.mesh = _textMesh.get();
	
	Matrix4 scale = math::Scaling(Vector3(_characterSize, _characterSize, 1));
	
	if (_is3D) {
		_worldMatrix = Transform()->TransformToWorldMatrix();
		
		_material.DepthTest(true);
		_material.DepthWrite(false);
	} else {
		Quaternion rotation = math::Rotation(0, Vector3(0,0,1));
		Matrix4 transform = Transform::GetRTMatrix(Vector3(_position, 0), rotation);
		_worldMatrix = transform;
		
		_material.DepthTest(false);
		_material.DepthWrite(false);
	}
	
	rop.is2D = !_is3D;
	_worldMatrix *= scale;
	
	rop.worldMatrix = &_worldMatrix;

	RenderPipeline *pipeline = GameObject()->RenderPipeline();
	pipeline->AddRenderOperation(rop);
}

//******************************************************************************
// Properrties

void TextRenderer::Text(const std::string &text) {
	
	_text = text;
	if (_font) {
		GenerateMesh(_textMesh.get(), _font, _text);
	} else {
		utils::Log("Can't generate text mesh without font");
	}
}

//------------------------------------------------------------------------------

void TextRenderer::Font(class Font *font) {
	
	_font = font;
	_material.Texture(font->FontTexture());
	_material.Blending(true);
	_material.SetBlendFunc(BlendFuncTransparent);
	GenerateMesh(_textMesh.get(), font, _text);
}


void TextRenderer::Is3D(bool is3D) {
	
	_is3D = is3D;

	if (_font) {
		GenerateMesh(_textMesh.get(), _font, _text);
	}
}

//******************************************************************************
//
//  Private
//
//******************************************************************************

void TextRenderer::GenerateMesh(Mesh *mesh, class Font *font, const std::string &text) {

	int characterCount = text.length();
	int realCharacterCount = 0;
	
	const int numVerticesInChar = 4;
	const int numFacesInChar = 2;
	
	std::unique_ptr<Vector3[]> vertexes = std::unique_ptr<Vector3[]>(new Vector3[characterCount * numVerticesInChar]);
	Vector3 *vertexDataPointer = vertexes.get();

	std::unique_ptr<Vector2[]> texCoord = std::unique_ptr<Vector2[]>(new Vector2[characterCount * numVerticesInChar]);
	Vector2 *texCoordDataPointer = texCoord.get();
	
	std::unique_ptr<unsigned short[]> indexes = std::unique_ptr<unsigned short[]>(new unsigned short[characterCount * Mesh::NUM_VERTEXES_IN_POLYGON * numFacesInChar]);
	unsigned short *indexDataPointer = indexes.get();
	
	Vector3 currentPosition = Vector3(0);
	
	for (int i = 0; i < characterCount; i++) {
		unsigned char c = text[i];
		FontCharacterData characterData;
		
		float spacingAddition = 0;
		
		if (c == ' ') {
			spacingAddition = 4;
		}
		
		if (c == '\n') {
			currentPosition.x = 0;
			currentPosition.y += font->UVSize() * _characterSize;
		} else if (font->GetCharacterData(c, characterData)) {
			
			// position
			
			Vector2 realSize = Vector2(characterData.uvSize.x * _characterSize, characterData.uvSize.y * _characterSize);
			Vector3 positions[numVerticesInChar];
			positions[0] = Vector3(0, 0, 0);
			positions[1] = Vector3(0, realSize.y, 0);
			positions[2] = Vector3(realSize.x, realSize.y, 0);
			positions[3] = Vector3(realSize.x, 0, 0);
			
			Vector3 offset = Vector3(characterData.uvOffset.x * _characterSize, characterData.uvOffset.y * _characterSize, 0);
			
			for (int j = 0; j < numVerticesInChar; j++) {
				vertexDataPointer[realCharacterCount * numVerticesInChar + j] = currentPosition + positions[j] - offset;
			}
			
			float spacing = (_letterSpacing + spacingAddition) * _characterSize * font->UVSize() / 10;
			currentPosition += Vector3(characterData.uvAdvance.x * _characterSize + spacing, 0, 0);
			
			// UV
			
			texCoordDataPointer[realCharacterCount * numVerticesInChar + 0] = Vector2(characterData.uvPos.x, characterData.uvPos.y);
			texCoordDataPointer[realCharacterCount * numVerticesInChar + 1] = Vector2(characterData.uvPos.x, characterData.uvPos.y + characterData.uvSize.y);
			texCoordDataPointer[realCharacterCount * numVerticesInChar + 2] = Vector2(characterData.uvPos.x + characterData.uvSize.x, characterData.uvPos.y + characterData.uvSize.y);
			texCoordDataPointer[realCharacterCount * numVerticesInChar + 3] = Vector2(characterData.uvPos.x + characterData.uvSize.x, characterData.uvPos.y);
		
			// Indexes
			
			unsigned short indexValues[] = {0,1,2,2,3,0};
			int numIndexesInChar = Mesh::NUM_VERTEXES_IN_POLYGON * numFacesInChar;
			for (int j = 0; j < numIndexesInChar; j++) {
				indexDataPointer[realCharacterCount * numIndexesInChar + j] = realCharacterCount * numVerticesInChar + indexValues[j];
			}
			
			realCharacterCount++;
		}
	}
	
	_textMesh->SetRenderData(vertexDataPointer, realCharacterCount * numVerticesInChar, indexDataPointer, realCharacterCount * numFacesInChar);
	_textMesh->SetUV0(texCoordDataPointer);
}


