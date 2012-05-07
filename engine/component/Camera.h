//
//  Camera.h
//  Cpptest
//
//  Created by Nikita on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"
#include "MyMath.h"

class Camera: public Component {
public:
	GENERATE_COMPONENT_ID(Camera)
	
	static Camera* Main() { return _mainCamera; }
	
	virtual void Awake();
	virtual void Update();
	virtual void PreRender();
	
	void CalculateMatrix();
	
	const Matrix4& WorldMatrix() const { return _worldMatrix; }
	const Matrix4& ProjectionMatrix() const { return _projectionMatrix; }
	
private:
	static Camera *_mainCamera;
	Matrix4 _worldMatrix;
	Matrix4 _projectionMatrix;
};

#endif
