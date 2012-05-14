//
//  Font.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Font.h"
#include "Utils.h"
#include <memory>

static FT_Library library;



bool Font::Load(const std::string& name) {

	bool result = false;
	
	std::string fullPath;
	if (utils::GetResourcePath(name, fullPath)) {

		std::ifstream stream(fullPath, std::ifstream::binary);
		
		if (stream.good()) {
			result = Load(stream);
		}
		
		stream.close();
	}
	
	if (result) {
		utils::Log("Font loaded: " + name);
	} else {
		utils::Log("Error loading font: " + name);
	}
	
	return result;
}


bool Font::Load(std::istream &stream) {
	
	bool result = false;
	
	try {
		stream.exceptions(std::istream::badbit | std::istream::failbit);
		stream.seekg(0, std::istream::end);
		int size = stream.tellg();
		stream.seekg(0, std::istream::beg);

		std::unique_ptr<unsigned char[]> buffer = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
		stream.read((char*)buffer.get(), size);
		
		FT_Face face;
		
		bool error = FT_New_Memory_Face(library, buffer.get(), size, 0, &face);
		
		if (!error) {
			
			GenerateFontTexture(face);
			result = true;
		}
		
	} catch (std::exception e) {
		// false returned
	}
	
	return result;
}


void Font::GenerateFontTexture(const FT_Face &face) {
	
	float textureSize = 256;
	float pixelSize = 20;
	
	FT_Set_Pixel_Sizes(face, pixelSize, pixelSize);
	
	FT_GlyphSlot slot = face->glyph;
	
	_uvSize = pixelSize / (float)textureSize;
	
	bool error;
	
	float currentBottomPoint = 2;
	float currentRightPoint = 0;
	
	float characterOffset = 0.5 * pixelSize;
//	float characterOffset = 0;
	
	std::unique_ptr<GLubyte[]> dataPtr = std::unique_ptr<GLubyte[]>( new GLubyte[(int)textureSize * (int)textureSize * 2] );
	GLubyte *data = dataPtr.get();
	
	unsigned char prev = 0;
	
	memset(data, 0, textureSize * textureSize * 2);
	
	for (int i = 32; i < 128; i++) {

		int glyphIndex = FT_Get_Char_Index(face, i);
		
		error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER);
		if (error) continue;
		
//		face->glyph->top;
		
		float width = slot->bitmap.width;
		float height = slot->bitmap.rows;
		
		if (currentRightPoint + width + characterOffset > textureSize) {
			currentRightPoint = characterOffset;
			currentBottomPoint += height + characterOffset;
		}
		
		_characterData[i].uvPos = Vector2(currentRightPoint / (float)textureSize, currentBottomPoint / (float)textureSize);
		_characterData[i].uvSize = Vector2(width / (float)textureSize, height / (float)textureSize);
		_characterData[i].pixelSize = Vector2(width, height);
//		_characterData[i].uvOffset = Vector2(face->glyph->bitmap_left / (float)textureSize, face->glyph->bitmap_top / (float)textureSize);
		_characterData[i].uvOffset = Vector2(0, face->glyph->bitmap_top / (float)textureSize);
//		_characterData[i].uvAdvance = Vector2(face->glyph->advance.x / 64 / (float)textureSize, face->glyph->advance.y / 64 / (float)textureSize);
//		_characterData[i].uvAdvance = Vector2((face->glyph->metrics.width / 64 - face->glyph->bitmap_left) / (float)textureSize, face->glyph->advance.y / 64 / (float)textureSize);
		_characterData[i].uvAdvance = Vector2((width) / (float)textureSize, face->glyph->advance.y / 64 / (float)textureSize);
		
		for (int k = 0; k < width; k++) {
			for (int j = 0; j < height; j++) {
				int index = k + (int)currentRightPoint + (int)((j+currentBottomPoint)*textureSize);
				GLubyte val = (GLubyte)slot->bitmap.buffer[k + j*(int)width];
				data[index * 2 + 0] = 255;
				data[index * 2 + 1] = val;
			}
		}
		
		currentRightPoint += width + characterOffset;
	}
	
	GLuint texture;
	
	glGenTextures(1, &texture);
	glBindTexture( GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, textureSize, textureSize, 0, GL_LUMINANCE_ALPHA , GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	_texture = TexturePtr(new Texture());
	_texture->SetAsNameAndID("font texture", texture);
	
}


bool Font::GetCharacterData(unsigned char index, FontCharacterData &outCharacterData) {
	
	bool result = false;
	
	if (index < 128) {
		outCharacterData = _characterData[index];
		result = true;
	}
	
	return result;
}

namespace freetype {

	
	void Init() {
		
		bool error = FT_Init_FreeType(&library);
		if (error) {
			utils::Log("Error initializing FreeType");
			return;
		}
		
	}
	
}