//
//  Platform_iOS.m
//  Cpptest
//
//  Created by Nikita on 5/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Platform_iOS.h"
#include <string>
#include <sys/time.h>

Platform_iOS::Platform_iOS(GameView *view) {
	
	_startTime = 0;
	_startTime = GetTime();
    _view = view;
    
    int touchPointersSize = sizeof(_touchPointers);
    memset(_touchPointers, 0, touchPointersSize);
}


void Platform_iOS::SetTouches(const input::TouchList& list) {
	
	_touches = list;
}


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

const input::TouchList& Platform_iOS::GetTouches() {
	
	return _touches;
}


int Platform_iOS::GetTouchID(UITouch *touch) {
    
    int result = -1;
    
    for (int i = 0; i < IOS_MAX_TOUCHES; i++) {
        if (_touchPointers[i] == touch) {
            result = i;
        }
    }
    
    return result;
}


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


void Platform_iOS::RemoveTouch(UITouch *touch) {
    
    int touchIndex = GetTouchID(touch);

    if (touchIndex >= 0) {
        _touchPointers[touchIndex] = NULL;
    }
}


void Platform_iOS::ProcessChangedTouches(NSSet *touches) {
    
	NSArray *allObjects = [touches allObjects];
	input::TouchList touchList;
	
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
	
	SetTouches(touchList);
	TouchesChanged(true);
}