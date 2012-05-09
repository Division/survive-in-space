//
//  Font.h
//  SurviveInSpace
//
//  Created by Nikita on 5/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FONT_H
#define FONT_H

#include <string>
#include "Resource.h"
#include <fstream>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Texture.h"
#include "Texture.h"

typedef struct {
	float x;
	float y;
	float width;
	float height;
	char *imageData;
} FontCharacterData;


class Font : public IResource {
public:
	
	virtual bool Load(const std::string& name);
	bool Load(std::istream &stream);

	Texture *FontTexture() { return _texture.get(); }
	
private:
	void GenerateFontTexture(const FT_Face &face);
	
private:
	TexturePtr _texture;
	FontCharacterData _characterData[128];
};

namespace freetype {

	void Init();
	
}

#endif
