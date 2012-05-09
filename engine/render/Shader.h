//
//  Shader.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "map"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "MyMath.h"
#include "Resource.h"

// Attributes used by engine
enum {
	EngineShaderParamPositionAttribute = 0,
	EngineShaderParamUV0Attribute,
	EngineShaderParamUV1Attribute,
	EngineShaderAttributesCount
};

// Uniforms used by engine
enum {
	EngineShaderParamModelViewMatrixUniform = EngineShaderAttributesCount,
	EngineShaderParamProjectionMatrixUniform,
	EngineShaderParamTexture0Uniform,
	EngineShaderParamTexture1Uniform,
	EngineShaderParamColorUniform,
	EngineShaderParamCount
};


class Shader {
public:
    Shader();
    ~Shader();
    
    bool Load(const std::string& name);
    bool Valid(void) const { return _IsValid; };
    void Use(void) const; 
    const std::string& Name() const { return _name; }
    
	bool ShaderUsesParameter(GLuint paramIndex);
	GLint GetShaderParameter(GLint paramIndex);
	
    int Attribute(const std::string& attribName);
    
    GLint GetUniformLocation(const std::string uniform) const;
	void SetUniform(GLint uniformIndex, const Matrix4& value);
    void SetUniform(const std::string& uniform, const Matrix4& value);
	void SetUniform(GLint uniformIndex, const Vector4& value);
    void SetUniform(const std::string& uniform, const Vector4& value);
	void SetUniform(GLint uniformIndex, int value);
    void SetUniform(const std::string& uniform, int value);

private:
    bool CompileShader(const std::string& source, GLenum shaderType, GLuint& outShaderHandle);
	void CheckEngineParamsUsed();
	
private:
	
    bool _IsValid;
    GLuint _programHandle;
    GLuint _vertexHandle;
    GLuint _fragmentHandle;
    std::string _name;
    std::map<std::string, GLint> _attributes;
    mutable std::map<std::string, GLint> _uniforms;
    GLint _engineParamsLocations[EngineShaderParamCount];
	
};

#endif
