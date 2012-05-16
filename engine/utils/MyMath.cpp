//
//  MyMath.cpp
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyMath.h"
#include <glm/ext.hpp>

namespace math {
    
    Matrix4 Translation(Vector3 const & offset) {
        
        return Translate(Matrix4(), offset);
    }
    
	Vector3 GetTranslation(const Matrix4& m) {

		Vector4 result = glm::column(m, 3);
		return Vector3(result);
	}
	
    Matrix4 RotationMatrix(float angle, Vector3 axis) {
        
        
        return Rotate(Matrix4(), angle, axis);
    }
	
    Quaternion Rotation(float angle, Vector3 axis) {
        
        
        return Rotate(Quaternion(), angle, axis);
    }

    
    Matrix4 Scaling(Vector3 const &factors) {
        
        return Scale(Matrix4(), factors);
    }

    
    Matrix4 Rotate(Matrix4 const &m, float angle, Vector3 const & axis) {
        
        return glm::rotate(m, angle, axis);
    }
	
    Vector3 Rotate(Vector3 const &v, const Quaternion &q) {
        
		Matrix4 m = glm::mat4_cast(q);
		
		Vector4 vec = m * Vector4(v,0);
		
		return Vector3(vec);
		
        //return glm::cross(v, q);
    }
	
    Quaternion Rotate(Quaternion const &q, float angle, Vector3 const & axis) {
        
        return glm::rotate(q, angle, axis);
    }
    
    Matrix4 Translate(Matrix4 const &m, Vector3 const & direction) {
        
        return glm::translate(m, direction);
    }
    
    Matrix4 Scale(Matrix4 const &m, Vector3 const factors) {
        
        return glm::scale(m, factors);
    }
    
    Matrix4 Transpose(Matrix4 const &m) {
        
        return glm::transpose(m);
    }
    
    Matrix4 Frustom(float left, float right, float bottom, float top, float zNear, float zFar) {
        
        return glm::frustum(left, right, bottom, top,zNear, zFar);
    }
    
    Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
        
        return glm::ortho(left, right, bottom, top, zNear, zFar);
    }
    
    Matrix4 LookAt(glm::vec3 const & eye, glm::vec3 const & center, glm::vec3 const & up) {
        
        return glm::lookAt(eye, center, up);
    }
    
    Matrix4 Ortho2D(float left, float right, float bottom, float top) {
        
        return glm::ortho(left, right, bottom, top);
    }
    
    Matrix4 Perspective(float fovy, float aspect, float zNear, float zFar) {
        
        return glm::perspective(fovy, aspect, zNear, zFar);
    }
    
    Vector3 Project(Vector3 const & obj, Matrix4 const & model, Matrix4 const & proj, Vector4 const & viewport) {
        
        return glm::project(obj, model, proj, viewport);
    }
    
    Vector3 UnProject(Vector3 const & win, Matrix4 const & model, Matrix4 const & proj, Vector4 const & viewport) {

        return glm::unProject(win, model, proj, viewport);
    }
	
	Vector3 Normalize(const Vector3 &v) {
		
		return glm::normalize(v);
	}
    
    float Length(const Vector3 &vector) {
        
        return glm::length(vector);
    }

    float Length(const Vector2 &vector) {
        
        return glm::length(vector);
    }
    
}
