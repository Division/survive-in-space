//
//  Render.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Platform specific code by XProger
//

#ifndef RENDER_H
#define RENDER_H

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

class Shader;
class Texture;
class Mesh;
class Material;

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#define GL_RGBA8 GL_RGBA8_OES
#define GL_LUMINANCE8 GL_LUMINANCE
#define GL_LUMINANCE8_ALPHA8 GL_LUMINANCE_ALPHA
#endif

#ifdef ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define GL_RGBA8 GL_RGBA8_OES
#define GL_LUMINANCE8 GL_LUMINANCE
#define GL_LUMINANCE8_ALPHA8 GL_LUMINANCE_ALPHA
#endif

#ifdef WIN32
#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>

#define glOrthof glOrtho

static void* _GetProcAddress(const char *name) {
    void* ptr = wglGetProcAddress(name);
    if (!ptr) printf("error %s\n", name);
    return ptr;
}

#define GetProcOGL(x) *(void**)&x=(void*)_GetProcAddress(#x);
#define GLOBAL __declspec(selectany) 

// Texture
GLOBAL PFNGLACTIVETEXTUREPROC glActiveTexture;
GLOBAL PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
// VBO
GLOBAL PFNGLGENBUFFERSARBPROC glGenBuffers;
GLOBAL PFNGLDELETEBUFFERSARBPROC glDeleteBuffers;
GLOBAL PFNGLBINDBUFFERARBPROC glBindBuffer;
GLOBAL PFNGLBUFFERDATAARBPROC glBufferData;
// GLSL
GLOBAL PFNGLGETPROGRAMIVPROC glGetProgramiv;
GLOBAL PFNGLCREATEPROGRAMPROC glCreateProgram;
GLOBAL PFNGLDELETEPROGRAMPROC glDeleteProgram;
GLOBAL PFNGLLINKPROGRAMPROC glLinkProgram;
GLOBAL PFNGLUSEPROGRAMPROC glUseProgram;
GLOBAL PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
GLOBAL PFNGLGETSHADERIVPROC glGetShaderiv;
GLOBAL PFNGLCREATESHADERPROC glCreateShader;
GLOBAL PFNGLDELETESHADERPROC glDeleteShader;
GLOBAL PFNGLSHADERSOURCEPROC glShaderSource;
GLOBAL PFNGLATTACHSHADERPROC glAttachShader;
GLOBAL PFNGLCOMPILESHADERPROC glCompileShader;
GLOBAL PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
GLOBAL PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
GLOBAL PFNGLUNIFORM1IVPROC glUniform1iv;
GLOBAL PFNGLUNIFORM1FVPROC glUniform1fv;
GLOBAL PFNGLUNIFORM2FVPROC glUniform2fv;
GLOBAL PFNGLUNIFORM3FVPROC glUniform3fv;
GLOBAL PFNGLUNIFORM4FVPROC glUniform4fv;
GLOBAL PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
GLOBAL PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
GLOBAL PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
GLOBAL PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
GLOBAL PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
GLOBAL PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
#endif                           

// DXT
#define GL_COMPRESSED_RGB_S3TC_DXT1			0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1		0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3		0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5		0x83F3
// PVRTC
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1		0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1		0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1		0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1		0x8C03
// ETC
#define GL_ETC1_RGB8_OES					0x8D64

static void InitOGL() {
#ifdef WIN32
	// Texture
    GetProcOGL(glActiveTexture);
    GetProcOGL(glCompressedTexImage2D);
	// VBO
    GetProcOGL(glGenBuffers);
    GetProcOGL(glDeleteBuffers);
    GetProcOGL(glBindBuffer);
    GetProcOGL(glBufferData);
	// GLSL
    GetProcOGL(glGetProgramiv);
    GetProcOGL(glCreateProgram);
    GetProcOGL(glDeleteProgram);
    GetProcOGL(glLinkProgram);
    GetProcOGL(glUseProgram);
    GetProcOGL(glGetProgramInfoLog);
    GetProcOGL(glGetShaderiv);
    GetProcOGL(glCreateShader);
    GetProcOGL(glDeleteShader);
    GetProcOGL(glShaderSource);
    GetProcOGL(glAttachShader);
    GetProcOGL(glCompileShader);
    GetProcOGL(glGetShaderInfoLog);
    GetProcOGL(glGetUniformLocation);
    GetProcOGL(glUniform1iv);
    GetProcOGL(glUniform1fv);
    GetProcOGL(glUniform2fv);
    GetProcOGL(glUniform3fv);
    GetProcOGL(glUniform4fv);
    GetProcOGL(glUniformMatrix3fv);
    GetProcOGL(glUniformMatrix4fv);
    GetProcOGL(glGetAttribLocation);
    GetProcOGL(glEnableVertexAttribArray);
    GetProcOGL(glDisableVertexAttribArray);
    GetProcOGL(glVertexAttribPointer);
#endif
}

#endif

