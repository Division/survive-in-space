//
//  Texture.cpp
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  PVR loading code by XProger
//

#include <iostream>
#include "Texture.h"
#include "Utils.h"
#include <fstream>
#include "MyMath.h"

Texture::Texture() {
    
    _isValid = false;
}


Texture::~Texture() {
    
    if (_isValid) {
        glDeleteTextures(1, &_handle);
    }
}


bool Texture::Load(const std::string& filename) {
    
	_isValid = false;
    bool result = false;
    _name = filename;
    std::string path;
	
    if (utils::GetResourcePath(filename, path)) {
        std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
        
        try {
            file.exceptions(std::ios::badbit | std::ios::failbit);
            
            PVR_TEXTURE_HEADER header;
            file.read((char*)&header, sizeof(PVR_TEXTURE_HEADER));
            
            bool mipMap = header.dwMipMapCount > 0;
            int mipCount = header.dwMipMapCount + 1;
            
            struct FormatInfo {
                bool compressed, alpha;
                int id, minX, minY, iformat, eformat, type;
            } info[] = {
                {false,	true,	PVR_RGBA8,	1,	1,	GL_RGBA8,							GL_RGBA,			GL_UNSIGNED_BYTE},\
                {false,	false,	PVR_I_8,	1,	1,	GL_LUMINANCE8,						GL_LUMINANCE,		GL_UNSIGNED_BYTE},\
                {false,	true,	PVR_AI_88,	1,	1,	GL_LUMINANCE8_ALPHA8,				GL_LUMINANCE_ALPHA,	GL_UNSIGNED_BYTE},\
                {true,	false,	PVR_PVRTC2,	16,	8,	GL_COMPRESSED_RGB_PVRTC_2BPPV1,		GL_FALSE,			GL_FALSE},\
                {true,	true,	PVR_PVRTC2,	16,	8,	GL_COMPRESSED_RGBA_PVRTC_2BPPV1,	GL_FALSE,			GL_FALSE},\
                {true,	false,	PVR_PVRTC4,	8,	8,	GL_COMPRESSED_RGB_PVRTC_4BPPV1,		GL_FALSE,			GL_FALSE},\
                {true,	true,	PVR_PVRTC4,	8,	8,	GL_COMPRESSED_RGBA_PVRTC_4BPPV1,	GL_FALSE,			GL_FALSE},\
                {true,	false,	PVR_DXT1,	4,	4,	GL_COMPRESSED_RGB_S3TC_DXT1,		GL_FALSE,			GL_FALSE},\
                {true,	true,	PVR_DXT1,	4,	4,	GL_COMPRESSED_RGBA_S3TC_DXT1,		GL_FALSE,			GL_FALSE},\
                {true,	true,	PVR_DXT3,	4,	4,	GL_COMPRESSED_RGBA_S3TC_DXT3,		GL_FALSE,			GL_FALSE},\
                {true,	true,	PVR_DXT5,	4,	4,	GL_COMPRESSED_RGBA_S3TC_DXT5,		GL_FALSE,			GL_FALSE},\
                {true,	false,	PVR_ETC,	4,	4,	GL_ETC1_RGB8_OES,					GL_FALSE,			GL_FALSE}
            };
            
            int		id = header.dwpfFlags & PVRTEX_PIXELTYPE;
            bool	alpha = (header.dwAlphaBitMask > 0);
            FormatInfo *fmt = NULL;
            for (int i = 0; i < sizeof(info) / sizeof(FormatInfo); i++)
                if (info[i].id == id && info[i].alpha == alpha) {
                    fmt = &info[i];
                    break;
                }
            
            if (!fmt) {
                utils::Log("invalid texture format");
                return false;
            }
            
            glGenTextures(1, &_handle);
            glBindTexture(GL_TEXTURE_2D, _handle);
            
            int sizeX = header.dwWidth,
            sizeY = header.dwHeight;
            
            for (int i = 0; i < mipCount; i++) {
                int size = (MAX(sizeX, fmt->minX) * MAX(sizeY, fmt->minY) * header.dwBitCount + 7) / 8;
                char *data;
                
                data = new char[size];
                file.read(data, size);
                if (fmt->compressed)
                    glCompressedTexImage2D(GL_TEXTURE_2D, i, fmt->iformat, sizeX, sizeY, 0, size, data);
                else
                    glTexImage2D(GL_TEXTURE_2D, i, fmt->iformat, sizeX, sizeY, 0, fmt->eformat, fmt->type, data);
                
                delete data;
                
                sizeX >>= 1;
                sizeY >>= 1;
            }
            
			std::cout << "Texture loaded: " << filename << " mipCount: " << mipCount << " [" << header.dwWidth << "," << header.dwHeight << "]\n";
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipMap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            result = true;
            _isValid = true;
            
            file.close();
            
        } catch (std::exception e) {
            // Do nothing, false returned
            _isValid = false;
        }
        
    }
    
    return result;
}


bool Texture::Bind(int samplerID) {
    
    if (_isValid) {
        glActiveTexture(GL_TEXTURE0 + samplerID);
        glBindTexture(GL_TEXTURE_2D, _handle);
        return true;
    } else {
        return false;
    }
}


bool Texture::Unbind(int samplerID) {
    
    if (_isValid) {
        glActiveTexture(GL_TEXTURE0 + samplerID);
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    } else {
        return false;
    }
}


void Texture::SetAsNameAndID(const std::string &name, GLuint id) {

	_name = name;
	_handle = id;
	_isValid = id > 0;
}