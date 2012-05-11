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
	
	FT_Set_Pixel_Sizes(face, 20, 20);
	
	FT_GlyphSlot slot = face->glyph;
	
	float textureSize = 256;
	
	bool error;
	
	float currentBottomPoint = 2;
	float currentRightPoint = 0;
	
	float characterOffset = 5;
	
	std::unique_ptr<GLubyte[]> dataPtr = std::unique_ptr<GLubyte[]>( new GLubyte[(int)textureSize * (int)textureSize] );
	GLubyte *data = dataPtr.get();
	
	memset(data, 0, textureSize * textureSize);
	
	for (int i = 32; i < 128; i++) {

		int glyphIndex = FT_Get_Char_Index(face, i);
		
		error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER);
		if (error) continue;
		
		float width = slot->bitmap.width;
		float height = slot->bitmap.rows;
		
		if (currentRightPoint + width + characterOffset > textureSize) {
			currentRightPoint = characterOffset;
			currentBottomPoint += height + characterOffset;
		}
		
		_characterData[i].x = currentRightPoint;
		_characterData[i].y = currentBottomPoint;
		_characterData[i].width = width;
		_characterData[i].height = height;
		
		for (int k = 0; k < width; k++) {
			for (int j = 0; j < height; j++) {
				int index = k + (int)currentRightPoint + (int)((j+currentBottomPoint)*textureSize);
				GLubyte val = (GLubyte)slot->bitmap.buffer[k + j*(int)width];
				data[index] = val;
				std::cout << val << " ";
			}
		}
		
		currentRightPoint += width + characterOffset;
		
	}
	
	GLuint texture;
	
	glGenTextures(1, &texture);
	glBindTexture( GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, textureSize, textureSize, 0, GL_LUMINANCE , GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texture);
	
	_texture = TexturePtr(new Texture());
	_texture->SetAsNameAndID("font texture", texture);
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