//
//  Input.h
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef INPUT_H
#define INPUT_H

#include "MyMath.h"
#include <vector>
#include "Platform.h"

namespace input {

	typedef enum {
		TouchPhaseBegan = 0,
		TouchPhaseMoved,
		TouchPhaseEnd,
		TouchPhaseStationary
	} TouchPhase;
	
	typedef platform::Touch Touch;
	
	typedef platform::TouchList TouchList;
	
	int TouchCount();
	const TouchList *Touches();
	Touch *GetTouch(int index);
	
	void Init(Platform *thePlatform);
	void Update();
	void PostUpdate();
}

#endif
