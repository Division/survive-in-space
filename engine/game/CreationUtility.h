//
//  CreationUtility.h
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CREATION_UTILITY_H
#define CREATION_UTILITY_H

#include "MyMath.h"

class GameObject;
class Scene;

namespace creation {

	void Init(Scene *theScene);
	
	void InitLevel();
	
	GameObject *CreateWorldContainer();
	
	GameObject *CreateBoxField(const Vector3& offset, float distance);
	
	GameObject *CreatePlayer(const Vector3 &position);

	GameObject *CreateCamera(const Vector3 &position);
	
	GameObject *CreateBox(const Vector3 &position);
}

#endif
