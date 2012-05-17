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

	static TouchList touchList;
	static TouchList newTouches;
	static Platform *platform;
	
	void Init(Platform *thePlatform) {
		
		platform = thePlatform;
	}
	
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
	
	int TouchCount() {
		
		return touchList.size();
	}
	
	const TouchList *Touches() {
		
		return &touchList;
	}

	Touch *GetTouch(int index) {
		
		Touch *result = NULL;
		if (index >= 0 && index < touchList.size()) {
			result = &touchList[index];
		}
		
		return result;
	}
	
	void Update() {
		
		if (platform->TouchesChanged()) {
			touchList = platform->GetTouches();
		}
        
//        PrintTouches(touchList);
	}
	
	bool IsTouchDead(const Touch& touch) {

		return touch.phase == TouchPhaseEnd;
	}
	
	void PostUpdate() {
		
		touchList.erase(std::remove_if(touchList.begin(), touchList.end(), IsTouchDead), touchList.end());
		for (TouchList::iterator it = touchList.begin(); it != touchList.end(); it++) {
			(*it).phase = (platform::TouchPhase)TouchPhaseStationary;
		}
	}

}