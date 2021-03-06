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
    
	float abs(float val) {
		
		return glm::abs(val);
	}
	
	int abs(int val) {
		
		return glm::abs(val);
	}
	
    Matrix4 Translation(Vector3 const & offset) {
        
        return Translate(Matrix4(), offset);
    }
    
	
	Matrix3 MatrixFromBasis(const Vector3 &left, const Vector3 &up, const Vector3 &front) {
		
		Matrix3 result;
		result = glm::column(result, 0, left);
		result = glm::column(result, 1, up);
		result = glm::column(result, 2, front);
		return result;
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
	
	Vector3 Cross(const Vector3 &v1, const Vector3 &v2) {
		
		return glm::cross(v1, v2);
	}
    
    float Length(const Vector3 &vector) {
        
        return glm::length(vector);
    }

    float Length(const Vector2 &vector) {
        
        return glm::length(vector);
    }
    
    
    
    bool PointInRect(const Vector2 &point, const Rect &rect) {
        
        bool inRect = true;
        
        if (point.x < rect.origin.x) inRect = false;
        else if (point.y < rect.origin.y) inRect = false;
        else if (point.x > rect.origin.x + rect.size.x) inRect = false;
        else if (point.y > rect.origin.y + rect.size.y) inRect = false;
        
        return inRect;
    }
    
    Rect::Rect(const Vector2 &center, const Vector2 &rectSize) {
        
        origin = center - rectSize / 2.0f;
        size = rectSize;
    }
    
    
    Rect::Rect(float x, float y, float width, float height) {
        
        origin = Vector2(x,y);
        size = Vector2(width,height);    
    }
    
    
    Rect::Rect() {
        
        origin = Vector2(0,0);
        size = Vector2(0,0);
    }
}
