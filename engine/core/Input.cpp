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
	
	int TouchCount(int messageID) {
		
		return platform->GetTouchCount(messageID);
	}

	
	int TouchMessageCount() {
        
        return platform->InputMessageCount();
    }
    
    
	Touch *GetTouch(int messageID, int touchIndex) {
		
		Touch *result = platform->GetTouch(messageID, touchIndex);
		
		return result;
	}
	
	bool IsTouchDead(const Touch& touch) {

		return touch.phase == TouchPhaseEnd;
	}

}