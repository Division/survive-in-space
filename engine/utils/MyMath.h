//
//  Math.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MYMATH_H
#define MYMATH_H

#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>

typedef glm::mat4 Matrix4;
typedef glm::mat3 Matrix3;
typedef glm::vec4 Vector4;
typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;
typedef glm::ivec3 Vector3i;
typedef glm::ivec2 Vector2i;
typedef glm::quat Quaternion;

#define DEG2RAD (M_PI/180)
#define RAD2DEG (180/M_PI)

#define GET_PTR(val) glm::value_ptr(val)

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

namespace math {

	Matrix4 Translation(Vector3 const & offset);    

	Matrix4 RotationMatrix(float angle, Vector3 axis);
    
	Vector3 GetTranslation(const Matrix4& m);
	
	Quaternion Rotate(Quaternion const &q, float angle, Vector3 const & axis);
	
	Vector3 Rotate(Vector3 const &v, const Quaternion &q);
	
	Quaternion Rotation(float angle, Vector3 axis);
	
    Matrix4 Scaling(Vector3 const &factors);
    
	Matrix4 Scale(Matrix4 const &m, Vector3 const factors);
    
	Matrix4 Rotate(Matrix4 const &m, float angle, Vector3 const & axis);
    
	Matrix4 Translate(Matrix4 const &m, Vector3 const & direction);
    
	Matrix4 Transpose(Matrix4 const &m);
    
	Matrix4 Frustom(float left, float right, float bottom, float top, float zNear, float zFar);
    
	Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
	Matrix4 LookAt(glm::vec3 const & eye, glm::vec3 const & center, glm::vec3 const & up);
    
	Matrix4 Ortho2D(float left, float right, float bottom, float top);
    
	Matrix4 Perspective(float fovy, float aspect, float zNear, float zFar);
    
	Vector3 Project(Vector3 const & obj, Matrix4 const & model, Matrix4 const & proj, Vector4 const & viewport);
    
	Vector3 UnProject(Vector3 const & win, Matrix4 const & model, Matrix4 const & proj, Vector4 const & viewport);

	Vector3 Normalize(const Vector3 &v);
    
    float Length(const Vector3 &vector);
    
    float Length(const Vector2 &vector);
    
}

#endif
