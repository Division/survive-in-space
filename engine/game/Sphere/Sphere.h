//
//  Sphere.h
//  Cpptest
//
//  Created by Nikita on 5/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Component.h"

class Transform;

class Sphere : public Component {
public:
	GENERATE_COMPONENT_ID(Sphere)
	
	virtual void Awake();
	
private:
	
	class Transform *triangles;
	class GameObject *sphereGeometry;
	
};

#endif
