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

Platform_iOS::Platform_iOS() {
	
	_startTime = 0;
	_startTime = GetTime();
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

Vector2 Platform_iOS::GetScreenResolution() {
	
	CGSize size = [[UIScreen mainScreen] bounds].size;
	CGFloat screenScale = [[UIScreen mainScreen] scale];
	return Vector2(size.width * screenScale, size.height * screenScale);
}

Vector2 Platform_iOS::GetInputResolution() {
	
	CGSize size = [[UIScreen mainScreen] bounds].size;
	return Vector2(size.width, size.height);
}

const input::TouchList& Platform_iOS::GetTouches() {
	
	return _touches;
}

double Platform_iOS::GetTime() {

    timeval time;
    gettimeofday(&time, NULL);
    double t = ((double)time.tv_sec + ((double)time.tv_usec / 1000000.0));
	return t - _startTime;
}