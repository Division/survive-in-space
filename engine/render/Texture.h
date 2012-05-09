//
//  Texture.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include "Render.h"
#include "Resource.h"

struct PVR_TEXTURE_HEADER {
	unsigned int dwHeaderSize;
	unsigned int dwHeight;
	unsigned int dwWidth;
	unsigned int dwMipMapCount;
	unsigned int dwpfFlags;
	unsigned int dwDataSize;
	unsigned int dwBitCount;
	unsigned int dwRBitMask;
	unsigned int dwGBitMask;
	unsigned int dwBBitMask;
	unsigned int dwAlphaBitMask;
	unsigned int dwPVR;
	unsigned int dwNumSurfs;
};

#define	PVRTEX_PIXELTYPE	0xff
#define	PVR_RGBA8	0x12
#define	PVR_I_8		0x16
#define	PVR_AI_88	0x17
#define	PVR_PVRTC2	0x18
#define	PVR_PVRTC4	0x19
#define	PVR_DXT1	0x20
#define	PVR_DXT3	0x22
#define	PVR_DXT5	0x24
#define	PVR_ETC		0x36

class Texture;
typedef std::unique_ptr<Texture> TexturePtr;
typedef std::map<std::string, TexturePtr> TextureMap;
typedef std::vector<TexturePtr> TextureList;

class Texture : public IResource {
public:
    Texture();
    ~Texture();
    
	std::string Name() { return _name; }
    bool Load(const std::string& filename);
	void SetAsNameAndID(const std::string &name, GLuint id);
    bool Bind(int samplerID = 0);
    bool Unbind(int samplerID = 0);
    GLuint Handle() { return _handle; }
	
private:
    GLuint _handle;
    bool _isValid;
	std::string _name;
};

#endif
