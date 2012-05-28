//
//  Mesh.cpp
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Mesh.h"
#include "Utils.h"

const int Mesh::VERTEX_STRIDE = 3;
const int Mesh::NORMAL_STRIDE = 3;
const int Mesh::UV_STRIDE = 2;
const int Mesh::NUM_VERTEXES_IN_POLYGON = 3;

//******************************************************************************
//
//  Public
//
//******************************************************************************

//******************************************************************************
// Construct/destruct

Mesh::Mesh() {
	
	_isValid = false;
	_vertexBuffer = 0;
	_indexBuffer = 0;
	_vertexCount = 0;
	_triangleCount = 0;
	_tag = 0;
	_hasNormals = false;
	_hasUV0 = false;
	_hasUV1 = false;
}

//------------------------------------------------------------------------------

Mesh::~Mesh() {
	
	FreeBuffers();
}

//******************************************************************************
// Loading

bool Mesh::Load(std::istream& readStream, bool useVBO) {
	
	if (_isValid) return false;
	
	try {
		readStream.exceptions(std::ios::badbit | std::ios::failbit);
		
		// Read header
		readStream.read((char *)&_tag, sizeof(int));
		readStream.read((char *)&_vertexCount, sizeof(int));
		readStream.read((char *)&_triangleCount, sizeof(int));
		
		// Calculating size values
		int vertexDataSize = _vertexCount * VERTEX_STRIDE * sizeof(float);
		int normalDataSize = vertexDataSize;
		int texCoordSize = _vertexCount * UV_STRIDE * sizeof(float);
		
		// Vertex data
		VertexAttribData tempVertexData = VertexAttribData(new char[vertexDataSize]);
		readStream.read(tempVertexData.get(), vertexDataSize);

		// Normal data
		char hasNormals;
		readStream.read(&hasNormals, sizeof(char));
		_hasNormals = hasNormals;
		
		VertexAttribData tempNormalData;
		if (_hasNormals) {
			tempNormalData = VertexAttribData(new char[normalDataSize]);
			readStream.read(tempNormalData.get(), normalDataSize);
		}
		
		// UV0 data
		char hasUV0;
		readStream.read(&hasUV0, sizeof(char));
		_hasUV0 = hasUV0;

		VertexAttribData tempUV0Data;
		if (_hasNormals) {
			tempUV0Data = VertexAttribData(new char[texCoordSize]);
			readStream.read(tempUV0Data.get(), texCoordSize);
		}
		
		// UV1 data
		char hasUV1;
		readStream.read(&hasUV1, sizeof(char));
		_hasUV1 = hasUV1;
		
		VertexAttribData tempUV1Data;
		if (_hasUV1) {
			tempUV1Data = VertexAttribData(new char[texCoordSize]);
			readStream.read(tempUV1Data.get(), texCoordSize);
		}

		
		// Index data
		int indexDataSize = _triangleCount * NUM_VERTEXES_IN_POLYGON * sizeof(unsigned short);
		IndexData tempIndexData = IndexData(new unsigned short[_triangleCount * NUM_VERTEXES_IN_POLYGON]);
		readStream.read((char *)tempIndexData.get(), indexDataSize);

		// VBO
		if (useVBO) {
			glGenBuffers(1, &_vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertexDataSize, tempVertexData.get(), GL_STATIC_DRAW);
			
			if (_hasNormals) {
				glGenBuffers(1, &_normalBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
				glBufferData(GL_ARRAY_BUFFER, normalDataSize, tempNormalData.get(), GL_STATIC_DRAW);				
			}
			
			if (_hasUV0) {
				glGenBuffers(1, &_uv0Buffer);
				glBindBuffer(GL_ARRAY_BUFFER, _uv0Buffer);
				glBufferData(GL_ARRAY_BUFFER, texCoordSize, tempUV0Data.get(), GL_STATIC_DRAW);								
			}
			
			if (_hasUV1) {
				glGenBuffers(1, &_uv1Buffer);
				glBindBuffer(GL_ARRAY_BUFFER, _uv1Buffer);
				glBufferData(GL_ARRAY_BUFFER, texCoordSize, tempUV1Data.get(), GL_STATIC_DRAW);								
			}
			
			glGenBuffers(1, &_indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, tempIndexData.get(), GL_STATIC_DRAW);
		}
		
		_indexData = std::move(tempIndexData);
		_vertexData = std::move(tempVertexData);
		
		if (_hasNormals) {
			_normalData = std::move(tempNormalData);
		}
		
		if (_hasUV0) {
			_uv0Data = std::move(tempUV0Data);
		}
		
		if (_hasUV1) {
			_uv1Data = std::move(tempUV1Data);
		}
		
		_useVBO = useVBO;
		
		_isValid = true;
	} catch (std::exception e) {
		// Error, false returned
	}
	
	return _isValid;
}

//******************************************************************************
// Generation

void Mesh::SetRenderData(void *vertexes, int vertexCount, unsigned short *triangles, int triangleCount) {
	
	if (vertexCount < Mesh::NUM_VERTEXES_IN_POLYGON || triangleCount < 1) {
		_isValid = false;
		return;
	}
	
	FreeBuffers();
	_vertexCount = vertexCount;
	_triangleCount = triangleCount;
	
	
	_vertexData = VertexAttribData(new char[VertexDataSize(vertexCount)]);
	_indexData = IndexData(new unsigned short[triangleCount * NUM_VERTEXES_IN_POLYGON]);
	
	memcpy(_vertexData.get(), vertexes, VertexDataSize(vertexCount));
	memcpy(_indexData.get(), triangles, IndexDataSize(triangleCount));

	_isValid = true;
	_hasNormals = false;
	_hasUV0 = false;
	_hasUV1 = false;
}

//------------------------------------------------------------------------------

void Mesh::SetNormals(void *normals) {
	
	_normalData = VertexAttribData(new char[VertexDataSize(_vertexCount)]);
	memcpy(_normalData.get(), normals, VertexDataSize(_vertexCount));
	_hasNormals = true;
}

//------------------------------------------------------------------------------

void Mesh::SetUV0(void *uv0) {
	
	_uv0Data = VertexAttribData(new char[UVDataSize(_vertexCount)]);
	memcpy(_uv0Data.get(), uv0, UVDataSize(_vertexCount));	
	_hasUV0 = true;
}

//------------------------------------------------------------------------------

void Mesh::SetUV1(void *uv1) {
	
	_uv1Data = VertexAttribData(new char[UVDataSize(_vertexCount)]);
	memcpy(_uv1Data.get(), uv1, UVDataSize(_vertexCount));		
	_hasUV1 = true;
}

//******************************************************************************
// Geometry access

bool Mesh::GetTriangleVertex(int triangleIndex, int vertexIndex, Vector3& outVertex) const {
	
	bool result = false;

	int dataIndex = GetVertexIndex(triangleIndex, vertexIndex);
	
	if (dataIndex >= 0 && dataIndex < _vertexCount) {
		int stride = VERTEX_STRIDE * sizeof(float);
		int offset = dataIndex * stride;
		outVertex =  *((Vector3 *)&_vertexData.get()[offset]);
		result = true;
	}

	return result;
}


bool Mesh::GetTriangleNormal(int triangleIndex, int normalIndex, Vector3& outNormal) const {
	
	if (!_hasNormals) return false;
	bool result = false;
	
	int dataIndex = GetVertexIndex(triangleIndex, normalIndex);
	
	if (dataIndex >= 0 && dataIndex < _vertexCount) {
		int stride = NORMAL_STRIDE * sizeof(float);
		int offset = dataIndex * stride;
		outNormal =  *((Vector3 *)&_normalData.get()[offset]);
		result = true;
	}
	
	return result;
}

//------------------------------------------------------------------------------

int Mesh::GetVertexIndex(int triangleIndex, int vertexIndex) const {

	if (triangleIndex < 0 || triangleIndex >= _triangleCount || vertexIndex < 0 || vertexIndex >= NUM_VERTEXES_IN_POLYGON) return -1;
	return _indexData.get()[triangleIndex * NUM_VERTEXES_IN_POLYGON + vertexIndex];
}

//******************************************************************************
// Render Data pointers

const char* Mesh::GetVertexDataPointer() const {
	
	char *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _vertexData.get();
	}
	
	return result;
}

//------------------------------------------------------------------------------

const char* Mesh::GetNormalDataPointer() const {

	char *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _normalData.get();
	}
	
	return result;
}

//------------------------------------------------------------------------------

const char* Mesh::GetUV0DataPointer() const {
	
	char *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _uv0Data.get();
	}
	
	return result;	
}

//------------------------------------------------------------------------------

const char* Mesh::GetUV1DataPointer() const {
	
	char *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _uv1Data.get();
	}
	
	return result;
}

//------------------------------------------------------------------------------

const unsigned short* Mesh::GetIndexDataPointer() const {
	
	unsigned short *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _indexData.get();
	}
	
	return result;
}


//******************************************************************************
//
//  Private
//
//******************************************************************************

//******************************************************************************
// Buffers

void Mesh::FreeBuffers() {
	
	if (_isValid && _useVBO) {
		glDeleteBuffers(1, &_vertexBuffer);
		glDeleteBuffers(1, &_indexBuffer);
		
		if (_hasNormals) {
			glDeleteBuffers(1, &_normalBuffer);
		}
		
		if (_hasUV0) {
			glDeleteBuffers(1, &_uv0Buffer);
		}
		
		if (_hasUV1) {
			glDeleteBuffers(1, &_uv1Buffer);
		}
	}	
	
	_useVBO = false;
}

//******************************************************************************
// Utils

int Mesh::VertexDataSize(int vertexCount) {
	return vertexCount * VERTEX_STRIDE * sizeof(float);
	
}

//------------------------------------------------------------------------------

int Mesh::UVDataSize(int vertexCount) {
	
	return vertexCount * UV_STRIDE * sizeof(float);
}

//------------------------------------------------------------------------------

int Mesh::IndexDataSize(int triangleCount) {
	
	return triangleCount * NUM_VERTEXES_IN_POLYGON * sizeof(unsigned short);	
}

