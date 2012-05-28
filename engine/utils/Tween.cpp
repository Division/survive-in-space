//
//  Tween.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Tween.h"
#include "CppTweener.h"
#include <vector>

namespace tween {

	typedef struct{
		TweenID id;
		cpptween::Tweener tweener;
	} TweenData;
	
	static std::vector<TweenData> tweenData;
	
	//******************************************************************************
	// Adding tweens
	
	
	
	//******************************************************************************
	// Update
	
	void Update() {
		
	}
	
}