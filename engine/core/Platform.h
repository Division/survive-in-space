//
//  Platform.h
//  Cpptest
//
//  Created by Nikita on 5/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include "MyMath.h"
#include <string>
#include <vector>

namespace platform {
	
	typedef enum {
		TouchPhaseBegan = 0,
		TouchPhaseMoved,
		TouchPhaseEnd,
		TouchPhaseStationary
	} TouchPhase;

	struct Touch {
		Vector3 position;
		Vector3 prevPosition;
		TouchPhase phase;
	};
	
	typedef std::vector<Touch> TouchList;
}

class Platform {
public:
	//******************************************************************************
	// Filesystem
	
	virtual bool GetResourcePath(const std::string& resourceName, std::string& outString) = 0;
	
	//******************************************************************************
	// Resolution
	
	virtual Vector2 GetScreenResolution() = 0;
	
	//******************************************************************************
	// Input
	
	virtual Vector2 GetInputResolution() = 0;
	
	virtual const platform::TouchList& GetTouches() = 0;
	
	virtual bool TouchesChanged() = 0;
	
	//******************************************************************************
	// Time
	
	// Returns time since app startup in seconds
	virtual double GetTime() = 0;
	
};

#endif
