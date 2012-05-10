//
//  Shader.cpp
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Shader.h"
#include "Utils.h"

static std::string EngineShaderParamNames [EngineShaderParamCount] = {
// Attributes first
	"Position",
	"Normal",
	"TexCoord0",
	"TexCoord1",
// Uniforms last
	"Modelview", 
	"Projection",
	"Texture0",
	"Texture1",
	"Color"
};

Shader::Shader() {
    
    _programHandle = 0;
    _vertexHandle = 0;
    _vertexHandle = 0;
    _IsValid = false;
    _name = "Unnamed shader";
	memset(_engineParamsLocations, -1, sizeof(_engineParamsLocations));
}


Shader::~Shader() {

    if (Valid()) {
        glDeleteProgram(_programHandle);
        glDeleteShader(_vertexHandle);
        glDeleteShader(_fragmentHandle);
        utils::Log("Shader unloaded: " + _name);
    }
}


void Shader::Use(void) const{
    
    if (Valid()) {
        glUseProgram(_programHandle);
    } else {
        // exception
    }
}


GLint Shader::GetUniformLocation(const std::string uniform) const {
    
    if (_uniforms.count(uniform)) {
        return _uniforms[uniform];
    }
    
    GLint location = glGetUniformLocation(_programHandle, uniform.c_str());
    _uniforms[uniform] = location;
    if (location == -1) {
        utils::Log("Error getting uniform " + uniform + " of shader " + _name);
    }
    
    return location;
}


void Shader::SetUniform(const std::string& uniform, const Matrix4& value) {
    
    glUniformMatrix4fv(GetUniformLocation(uniform), 1, GL_FALSE, GET_PTR(value));
}


void Shader::SetUniform(GLint uniformIndex, const Matrix4& value) {
    
    glUniformMatrix4fv(_engineParamsLocations[uniformIndex], 1, GL_FALSE, GET_PTR(value));
}


void Shader::SetUniform(GLint uniformIndex, const Vector4& value) {
	
	glUniform4fv(_engineParamsLocations[uniformIndex], 1, (GLfloat *)&value); 
}

void Shader::SetUniform(const std::string& uniform, const Vector4& value) {
    
    glUniform4fv(GetUniformLocation(uniform), 1, (GLfloat *)&value); 
}

void Shader::SetUniform(GLint uniformIndex, int value) {
    
    glUniform1i(_engineParamsLocations[uniformIndex], value);
}

void Shader::SetUniform(const std::string& uniform, int value) {
    
    glUniform1i(GetUniformLocation(uniform), value);
}


int Shader::Attribute(const std::string& attribName) {
    
	GLint attribLocation;
	
    if (_attributes.count(attribName)) {
		
        attribLocation = _attributes[attribName];
		
    } else {
		
		if(Valid()) {

			attribLocation = glGetAttribLocation(_programHandle, attribName.c_str());
			if (attribLocation == -1) {
				utils::Log("Attribute " + attribName + "doesn't exists in shader " + _name);
			}
			
		} else {
			
			utils::Log("Can't add attribute on invalid shader");
			attribLocation = -1;
		}
		
		_attributes[attribName] = attribLocation;
    }
	
	return attribLocation;
}


bool Shader::CompileShader(const std::string& source, GLenum shaderType, GLuint& outShaderHandle) {
    
    GLuint handle = glCreateShader(shaderType);
    
    const char *cstr = source.c_str();
    int length = source.length();
    
    glShaderSource(handle, 1, &cstr, &length);
    
    glCompileShader(handle);
    
    GLint compileSuccess;
    
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(handle, sizeof(messages), 0, &messages[0]);
        std::string messageString(messages);
        utils::Log("Error compiling shader: " + messageString);
        handle = 0;
    } else {
        outShaderHandle = handle;
    }
    
    return handle != 0;
}


bool Shader::Load(const std::string& name) {
    
    if (Valid()) return false;
    
    bool success = false;
    
    // Trying load and compile vertex shader
    
    std::string vsName = name + ".vs";
    bool useVS = false;    
    std::string vsContent;
    
    if (utils::GetTextFileContents(vsName, vsContent)) {
        // Shader source loaded
        if (CompileShader(vsContent, GL_VERTEX_SHADER, _vertexHandle)) {
            // Shader compiled
            useVS = true;
        } else {
            utils::Log("in " + vsName);
        }
    }
    
    // Trying load and compile fragment shader
    
    std::string fsName = name + ".fs";
    bool useFS = false;
    std::string fsContent;
    
    if (utils::GetTextFileContents(fsName, fsContent)) {
        // Shader source loaded
        if (CompileShader(fsContent, GL_FRAGMENT_SHADER, _fragmentHandle)) {
            // Shader compiled
            useFS = true;
        } else {
            utils::Log("in " + fsName);
        }
    }
    
    // Link progam
    
    if (useFS && useVS) {
        _programHandle = glCreateProgram();
        
        glAttachShader(_programHandle, _vertexHandle);
        glAttachShader(_programHandle, _fragmentHandle);
        glLinkProgram(_programHandle);
        
        GLint linkSuccess;
        glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_TRUE) {
            // link success
            success = true;
            _IsValid = true;
            _name = name;
			
			CheckEngineParamsUsed();
			
            utils::Log("Shader loaded: " + _name);
        } else {
            // link fail
            GLchar messages[256];
            glGetProgramInfoLog(_programHandle, sizeof(messages), 0, &messages[0]);
            std::string messageString(messages);
            utils::Log("Error linking shader: " + messageString);
            _programHandle = 0;
        }
    }
    
    return success;
}


void Shader::CheckEngineParamsUsed() {

	// Loop through all engine uniform and attribute name.
	// Check if shader supports them
	
	// Attributes
	for (int i = 0; i < EngineShaderAttributesCount; i++) {
		GLint attribLocation = glGetAttribLocation(_programHandle, EngineShaderParamNames[i].c_str());
		_engineParamsLocations[i] = attribLocation;
		if (attribLocation >= 0) {
			_attributes[EngineShaderParamNames[i]] = attribLocation;
		}
	}
	
	// Uniforms
	for (int i = EngineShaderAttributesCount; i < EngineShaderParamCount; i++) {
		GLint uniformLocation = glGetUniformLocation(_programHandle, EngineShaderParamNames[i].c_str());
		_engineParamsLocations[i] = uniformLocation;
		if (uniformLocation >= 0) {
			_uniforms[EngineShaderParamNames[i]] = uniformLocation;
		}
	}
}


bool Shader::ShaderUsesParameter(GLuint paramIndex) {

	return _engineParamsLocations[paramIndex] >= 0;
}


GLint Shader::GetShaderParameter(GLint paramIndex) {

	return _engineParamsLocations[paramIndex];
}