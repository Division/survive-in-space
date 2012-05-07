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

static const int NORMAL_SHIFT = 0;
static const int UV0_SHIFT = 1;
static const int UV1_SHIFT = 2;

const int Mesh::VERTEX_STRIDE = 3;
const int Mesh::NORMAL_STRIDE = 3;
const int Mesh::UV_STRIDE = 2;
const int Mesh::NUM_VERTEXES_IN_POLYGON = 3;

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


Mesh::~Mesh() {
	
	if (_useVBO) {
		
	}
}



bool Mesh::Load(std::istream& readStream, bool useVBO) {
	
	if (_isValid) return false;
	
	try {
		readStream.exceptions(std::ios::badbit | std::ios::failbit);
		
		// Read header
		int vertexDataKey;
		readStream.read((char *)&_tag, sizeof(int));
		readStream.read((char *)&vertexDataKey, sizeof(int));
		readStream.read((char *)&_vertexCount, sizeof(int));
		readStream.read((char *)&_triangleCount, sizeof(int));
		
		// Calculating size values
		int positionDataSize = _vertexCount * VERTEX_STRIDE * sizeof(float);
		int texCoordSize = _vertexCount * UV_STRIDE * sizeof(float);
		int vertexDataSize = positionDataSize + texCoordSize;
		
		// Vertex data
		VertexData tempVertexData = VertexData(new char[vertexDataSize]);
		readStream.read(tempVertexData.get(), vertexDataSize);

		// Index data
		int indexDataSize = _triangleCount * NUM_VERTEXES_IN_POLYGON * sizeof(unsigned short);
		IndexData tempIndexData = IndexData(new unsigned short[_triangleCount * NUM_VERTEXES_IN_POLYGON]);
		readStream.read((char *)tempIndexData.get(), indexDataSize);

		if (useVBO) {
			glGenBuffers(1, &_vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertexDataSize, tempVertexData.get(), GL_STATIC_DRAW);
			
			glGenBuffers(1, &_indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, tempIndexData.get(), GL_STATIC_DRAW);
		}
		
		_indexData = std::move(tempIndexData);
		_vertexData = std::move(tempVertexData);
		
		_useVBO = useVBO;
		
		// Vertex attribute usage
		_hasNormals = vertexDataKey & (1 << NORMAL_SHIFT);
		_hasUV0 = vertexDataKey & (1 << UV0_SHIFT);
		_hasUV1 = vertexDataKey & (1 << UV1_SHIFT);
		
		std::cout << "Mesh loaded, " << _triangleCount << " triangles";
		
		_isValid = true;
	} catch (std::exception e) {
		// Error, false returned
	}
	
	return _isValid;
}


int Mesh::GetVertexDataStride() const {

	return (VERTEX_STRIDE + UV_STRIDE) * sizeof(float);
}


bool Mesh::GetTriangleVertex(int triangleIndex, int vertexIndex, Vector3& outVertex) const {
	
	bool result = false;

	int dataIndex = GetVertexIndex(triangleIndex, vertexIndex);
	
	if (dataIndex >= 0 && dataIndex < _vertexCount) {
		int stride = GetVertexDataStride();
		int offset = dataIndex * stride;
		outVertex =  *((Vector3 *)&_vertexData.get()[offset]);
		result = true;
	}

	return result;
}


int Mesh::GetVertexIndex(int triangleIndex, int vertexIndex) const {

	if (triangleIndex < 0 || triangleIndex >= _triangleCount || vertexIndex < 0 || vertexIndex >= NUM_VERTEXES_IN_POLYGON) return -1;
	return _indexData.get()[triangleIndex * NUM_VERTEXES_IN_POLYGON + vertexIndex];
}

const char* Mesh::VertexDataPointer() const {
	
	char *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _vertexData.get();
	}
	
	return result;
}


const unsigned short* Mesh::IndexDataPointer() const {
	
	unsigned short *result = 0;
	
	if (_isValid && !_useVBO) {
		result = _indexData.get();
	}
	
	return result;
}
