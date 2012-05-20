//
//  Platform_iOS.m
//  Cpptest
//
//  Created by Nikita on 5/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Platform_iOS.h"
#include <iostream>
#include <string>
#include <sys/time.h>

Platform_iOS::Platform_iOS(GameView *view) {
	
	_startTime = 0;
	_startTime = GetTime();
    _view = view;
    _touchMessageCount = 0;
    
    int touchPointersSize = sizeof(_touchPointers);
    memset(_touchPointers, 0, touchPointersSize);
	_motionMonitor = [[MotionMonitor alloc] init];
}

//------------------------------------------------------------------------------

bool Platform_iOS::GetResourcePath(const std::string& resourceName, std::string& outString) {
	
	NSString *resourceString = [NSString stringWithCString:resourceName.c_str() encoding:NSUTF8StringEncoding];
	NSString *resultString = [[NSBundle mainBundle] pathForResource:resourceString ofType:nil];
	
	bool result = false;
	
	if (resultString) {
		outString = [resultString cStringUsingEncoding:NSUTF8StringEncoding];
		result = true;
	}
	
	return result;
}

//******************************************************************************
// Resolution


Vector2 Platform_iOS::GetScreenResolution() {
	
	CGSize size = CGSizeMake([_view drawableWidth], [_view drawableHeight]);
	return Vector2(size.width, size.height);
}

//------------------------------------------------------------------------------

Vector2 Platform_iOS::GetInputResolution() {
	
	CGSize size = CGSizeMake([_view drawableWidth], [_view drawableHeight]);
	CGFloat screenScale = [[UIScreen mainScreen] scale];
	return Vector2(size.width / screenScale, size.height / screenScale);
}

//******************************************************************************
// Time

double Platform_iOS::GetTime() {

    timeval time;
    gettimeofday(&time, NULL);
    double t = ((double)time.tv_sec + ((double)time.tv_usec / 1000000.0));
	return t - _startTime;
}


//******************************************************************************
// Touches

bool IsTouchDead(const input::Touch& touch) {
    
    return touch.phase == platform::TouchPhaseEnd;
}

//------------------------------------------------------------------------------

void Platform_iOS::ClearTouchMessages() {

    if (_touchMessageCount > 1) {
        _touchMessages[0] = _touchMessages[_touchMessageCount - 1];
        _touchMessageCount = 1;
    }
    
    if (_touchMessageCount == 1) {
        
        _touchMessages[0].erase(std::remove_if(_touchMessages[0].begin(), _touchMessages[0].end(), IsTouchDead), _touchMessages[0].end());
        
        for (int i = GetTouchCount(0) - 1; i >= 0; i--) {
            input::Touch *touch = GetTouch(0, i);
            touch->phase = platform::TouchPhaseStationary;
        }
        
        if (GetTouchCount(0) == 0) {
            _touchMessageCount = 0;
        }
    }
    
}

//------------------------------------------------------------------------------

int Platform_iOS::InputMessageCount() {
    
    return _touchMessageCount;
}

//------------------------------------------------------------------------------

int Platform_iOS::GetTouchCount(int messageID) {
    
    if (messageID < 0 || messageID >= _touchMessageCount) return 0;
    
    return _touchMessages[messageID].size();
}

//------------------------------------------------------------------------------

platform::Touch * Platform_iOS::GetTouch(int messageID, int touchID) {

    if (messageID < 0 || messageID >= _touchMessageCount) return NULL;
    if (touchID < 0 || touchID >= GetTouchCount(messageID)) return NULL;
    
    return &(_touchMessages[messageID][touchID]);
}

//------------------------------------------------------------------------------

int Platform_iOS::GetTouchID(UITouch *touch) {
    
    int result = -1;
    
    for (int i = 0; i < IOS_MAX_TOUCHES; i++) {
        if (_touchPointers[i] == touch) {
            result = i;
        }
    }
    
    return result;
}

//------------------------------------------------------------------------------

int Platform_iOS::AddTouch(UITouch *touch) {
   
    int result = -1;
    
    for (int i = 0; i < IOS_MAX_TOUCHES; i++) {
        if (_touchPointers[i] == NULL) {
            result = i;
            _touchPointers[i] = touch;
            break;
        }
    }

    return result;
}

//------------------------------------------------------------------------------

void Platform_iOS::RemoveTouch(UITouch *touch) {
    
    int touchIndex = GetTouchID(touch);

    if (touchIndex >= 0) {
        _touchPointers[touchIndex] = NULL;
    }
}

//------------------------------------------------------------------------------

void Platform_iOS::ProcessChangedTouches(NSSet *touches) {
    
	if (_touchMessageCount == IOS_MAX_TOUCH_MESSAGES) {
		NSLog(@"Max touch messages reached");
		return;
	}
	
    input::TouchList &touchList = _touchMessages[_touchMessageCount];
    _touchMessageCount++;
    touchList.resize(0);
    
	NSArray *allObjects = [touches allObjects];
    
	for (UITouch *touch in allObjects) {
		CGPoint location = [touch locationInView:_view];
		CGPoint prevLocation = [touch previousLocationInView:_view];
		
		input::Touch gameTouch;
		gameTouch.position = Vector3(location.x, location.y, 0);
		gameTouch.prevPosition = Vector3(prevLocation.x, prevLocation.y, 0);
		
        int touchIndex = -1;
        
		switch (touch.phase) {
			case UITouchPhaseBegan:
				gameTouch.phase = platform::TouchPhaseBegan;
                touchIndex = GetTouchID(touch);
                if (touchIndex == -1) {
                    touchIndex = AddTouch(touch);
                }
                gameTouch.id = touchIndex;

				break;
                
			case UITouchPhaseMoved:
				gameTouch.phase = platform::TouchPhaseMoved;
                gameTouch.id = GetTouchID(touch);
				break;
				
			case UITouchPhaseStationary:
				gameTouch.phase = platform::TouchPhaseStationary;
                gameTouch.id = GetTouchID(touch);
                break;
                
			case UITouchPhaseCancelled:
			case UITouchPhaseEnded:
				gameTouch.phase = platform::TouchPhaseEnd;
                gameTouch.id = GetTouchID(touch);
                RemoveTouch(touch);
				break;
		}
		
		touchList.push_back(gameTouch);
	}
}

//******************************************************************************
// Motion

bool Platform_iOS::GetGyroData(Vector3 &outData) {
	
	bool result = false;

	CMGyroData *data = _motionMonitor.gyroData;
	if (data) {
		result = true;
		outData = Vector3(data.rotationRate.x, data.rotationRate.y, data.rotationRate.z);
	}

	return result;
}

//------------------------------------------------------------------------------

bool Platform_iOS::GetAccelerometerData(Vector3 &outData) {
	
	bool result = false;
	
	CMAccelerometerData *data = _motionMonitor.accelerometerData;
	if (data) {
		result = true;
		outData = Vector3(data.acceleration.x, data.acceleration.y, data.acceleration.z);
	}
	
	return result;
}
