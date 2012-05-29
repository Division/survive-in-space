//
//  Spawn.h
//  SurviveInSpace
//
//  Created by Nikita on 5/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SPAWN_H
#define SPAWN_H

#include "Component.h"

class Spawn : public Component {
public:
	GENERATE_COMPONENT_ID(Spawn)
	
	Vector3 normal;
	Vector3 position;
	Quaternion q;
	
	Spawn();
	~Spawn();
	
	void Update();
	
private:
	float _angle;
};

#endif
