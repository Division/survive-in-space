//
//  Platform_iOS.h
//  Cpptest
//
//  Created by Nikita on 5/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Platform.h"
#include "Input.h"

class Platform_iOS : public Platform {
public:
	Platform_iOS();
	
	//******************************************************************************
	// Touch input
	
	void SetTouches(const input::TouchList& list);
	void TouchesChanged(bool changed) { _touchesChanged = changed; };
	
	//******************************************************************************
	// Platform abstract methods
	
	bool GetResourcePath(const std::string& resourceName, std::string& outString);
	
	Vector2 GetScreenResolution();
	
	Vector2 GetInputResolution();
	
	const input::TouchList& GetTouches();
	
	bool TouchesChanged() { return _touchesChanged; };
	
	double GetTime();

private:
	double _startTime;
	input::TouchList _touches;
	bool _touchesChanged;
};