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

#define IOS_MAX_TOUCHES 11
#define IOS_MAX_TOUCH_MESSAGES 5

class Platform_iOS : public Platform {
public:
	Platform_iOS(GameView *view);
	
	//******************************************************************************
	// Touch input
	
    void ClearTouchMessages();
	void SetTouches(const input::TouchList& list);
	void TouchesChanged(bool changed) { _touchesChanged = changed; };
	void ProcessChangedTouches(NSSet *touches);
    
	//******************************************************************************
	// Platform abstract methods
	
	bool GetResourcePath(const std::string& resourceName, std::string& outString);
	
	Vector2 GetScreenResolution();
	
	Vector2 GetInputResolution();
	
	const input::TouchList& GetTouches();
	
	bool TouchesChanged() { return _touchesChanged; };
    int InputMessageCount();
    int GetTouchCount(int messageID);
    platform::Touch * GetTouch(int messageID, int touchID);

	double GetTime();
    

private:
    int GetTouchID(UITouch *touch);
    int AddTouch(UITouch *touch);
    void RemoveTouch(UITouch *touch);
    
private:
	double _startTime;
	input::TouchList _touches;
	bool _touchesChanged;
    GameView *_view;
  
    
    void *_touchPointers[IOS_MAX_TOUCHES];
    input::TouchList _touchMessages[IOS_MAX_TOUCH_MESSAGES];
    int _touchMessageCount;
};