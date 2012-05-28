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
#include <vector>

class Transform;
class Spawn;

class Sphere : public Component {
public:
	GENERATE_COMPONENT_ID(Sphere)
	
	virtual void Awake();
	
private:
	void InitSpawns();
	void CreateSpawn(const class Transform *transform);
	
private:
	std::vector<Spawn *> _spawns;
	class Transform *_triangles;
	class GameObject *_sphereGeometry;
	
};

#endif
