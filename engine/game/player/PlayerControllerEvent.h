//
//  PlayerControllerEvent.h
//  SurviveInSpace
//
//  Created by Nikita on 5/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PLAYER_CONTROLLER_EVENT_H
#define PLAYER_CONTROLLER_EVENT_H

#include "Event.h"
#include <string>

class PlayerControllerEvent : public Event {
public:
	GENERATE_EVENT_ID(PlayerControllerEvent)
	
	enum { CONTROL_CHANGED = 1 };
	
	Vector3 sticker;
	float acceleration;
};

#endif
