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
#import "GameView.h"
#import "MotionMonitor.h"

#define IOS_MAX_TOUCHES 11
#define IOS_MAX_TOUCH_MESSAGES 20

class Platform_iOS : public Platform {
public:
	Platform_iOS(GameView *view);
	
	//******************************************************************************
	// Touch input
	
    void ClearTouchMessages();
	void ProcessChangedTouches(NSSet *touches);
    
	//******************************************************************************
	// Platform abstract methods
	
	//-------------------
	// Resource
	bool GetResourcePath(const std::string& resourceName, std::string& outString);
	
	//-------------------
	// Resolution
	Vector2 GetScreenResolution();
	Vector2 GetInputResolution();
	
	//-------------------
	// Touch Input
    int InputMessageCount();
    int GetTouchCount(int messageID);
    platform::Touch * GetTouch(int messageID, int touchID);

	//-------------------
	// Time
	double GetTime();
	
	//-------------------
	// Motion
	bool GetGyroData(Vector3 &outData);
	bool GetAccelerometerData(Vector3 &outData);
    
private:
    int GetTouchID(UITouch *touch);
    int AddTouch(UITouch *touch);
    void RemoveTouch(UITouch *touch);
    
private:
	double _startTime;
    GameView *_view;
    
    void *_touchPointers[IOS_MAX_TOUCHES];
    input::TouchList _touchMessages[IOS_MAX_TOUCH_MESSAGES];
    int _touchMessageCount;
	MotionMonitor *_motionMonitor;
};