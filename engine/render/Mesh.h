//
//  Mesh.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MESH_H
#define MESH_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include "MyMath.h"

class Mesh;

typedef std::unique_ptr<Mesh> MeshPtr;
typedef std::vector<MeshPtr> MeshList;

typedef std::unique_ptr<char[]> VertexData;
typedef std::unique_ptr<unsigned short> IndexData;

class Mesh {
public:
	static const int VERTEX_STRIDE;
	static const int NORMAL_STRIDE;
	static const int UV_STRIDE;
	static const int NUM_VERTEXES_IN_POLYGON;
	
    Mesh();
    ~Mesh();
    
	// Loading
    bool Load(std::istream& readStream, bool useVBO);
	
	// Mesh properties
    bool IsValid() const { return _isValid; }
	int Tag() const { return _tag; }
	int TriangleCount() const { return _triangleCount; }
	int VertexCount() const { return _vertexCount; }
	bool UsesVBO() const { return _useVBO; }
	
	// Render data accessors
	bool GetTriangleVertex(int triangleIndex, int vertexIndex, Vector3& outVertex) const;
	int GetVertexIndex(int triangleIndex, int vertexIndex) const;
	int GetVertexDataStride() const;
	
	// no VBO
	const char* VertexDataPointer() const;
	const unsigned short* IndexDataPointer() const;
	
	// VBO
	GLuint GetVertexBuffer() const { return _vertexBuffer; }
	GLuint GetIndexBuffer() const { return _indexBuffer; }

private:
	// Mesh properties
    bool _isValid;
	int _tag;
	int _triangleCount;
	int _vertexCount;
	
	// VBO
	GLuint _vertexBuffer;
	GLuint _indexBuffer;
	bool _useVBO;

	// Mesh data [null if VBO used]
	VertexData _vertexData;
	IndexData _indexData;
	
	// Vertex attributes available
	bool _hasNormals;
	bool _hasUV0;
	bool _hasUV1;
	
};

#endif
