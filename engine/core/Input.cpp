//
//  Input.cpp
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Input.h"

namespace input {

	static Platform *platform;
	
	//******************************************************************************
	// Touch
	
	void PrintTouches(const TouchList &touches) {

		int i = 0;
		
		if (touches.size() == 0) {
			std::cout << "NO TOUCHES\n";
		}
		
		for (TouchList::const_iterator it = touches.begin(); it != touches.end(); it++) {
			std::cout << (*it).id << ": (" << (*it).position.x << "," << (*it).position.y << " phase: " << (*it).phase << "\n";
			i++;
		}
	}
	
	//------------------------------------------------------------------------------
	
	void PrintTouchesCount() {
		
		std::cout << "- - - - - - - - - - - - - - - - - \n";
		
		std::cout << "queue count: " << platform->InputMessageCount() << "\n";
		for (int i = 0; i < platform->InputMessageCount(); i++) {
			std::cout << " cnt [" << i << "] : " << platform->GetTouchCount(i) << "\n";
			
			for (int j = 0; j < platform->GetTouchCount(i); j++) {
				std::cout << "      " <<  platform->GetTouch(i, j)->id << ": " << "(" << platform->GetTouch(i, j)->phase << ") \n";
			}
			
			 
		}
	}
	
	//------------------------------------------------------------------------------
	
	int TouchCount(int messageID) {
		
		return platform->GetTouchCount(messageID);
	}

	//------------------------------------------------------------------------------
	
	int TouchMessageCount() {
        
        return platform->InputMessageCount();
    }
    
	//------------------------------------------------------------------------------
    
	Touch *GetTouch(int messageID, int touchIndex) {
		
		Touch *result = platform->GetTouch(messageID, touchIndex);
		
		return result;
	}
	
	//------------------------------------------------------------------------------
	
	bool IsTouchDead(const Touch& touch) {

		return touch.phase == TouchPhaseEnd;
	}
	
	//******************************************************************************
	// Motion
	
	static Vector3 currentAccelerometer;
	static bool accelerometerReady;
	static Vector3 currentGyro;
	static bool gyroReady;
	
	Vector3 LowPassFilter(const Vector3 &newValue, const Vector3 &prevValue, float filterFactor) {
		
		return newValue * filterFactor + prevValue * (1 - filterFactor);
	}
	
	Vector3 HighPassFilter(const Vector3 &newValue, const Vector3 &prevValue, float filterFactor) {
		
		return newValue - (newValue * filterFactor + prevValue * (1 - filterFactor));
	}
	
	//------------------------------------------------------------------------------
	
	void UpdateMotionData() {
		
		Vector3 newAccelerometeValue;
		accelerometerReady = platform->GetAccelerometerData(newAccelerometeValue);
		if (accelerometerReady) {
			currentAccelerometer = LowPassFilter(newAccelerometeValue, currentAccelerometer, 0.5);
		}
		
		Vector3 newGyroData;
		gyroReady = platform->GetGyroData(newGyroData);
		if (gyroReady) {
			currentGyro = newGyroData;
		}
	}

	//------------------------------------------------------------------------------
	
	bool GetGyroData(Vector3 &outData) {
		
		bool result = false;
		
		if (gyroReady) {
			result = true;
			outData = currentGyro;
		}
			
		return result;
	}
	
	//------------------------------------------------------------------------------
	
	bool GetAccelerometerData(Vector3 &outData) {
	
		bool result = false;
		
		if (accelerometerReady) {
			result = true;
			outData = currentAccelerometer;
		}
		
		return result;
	}
	
	//******************************************************************************
	// Init/Update

	void Init(Platform *thePlatform) {
		
		platform = thePlatform;
	}
	
	//------------------------------------------------------------------------------
	
	void Update() {
		UpdateMotionData();
	}

}
