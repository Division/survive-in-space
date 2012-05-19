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

//******************************************************************************
//
//  PlayerControllerEvent
//
//******************************************************************************

// Used to tell player ship it's current controls values
class TouchPlayerControllerEvent : public Event {
public:
	GENERATE_EVENT_ID(TouchPlayerControllerEvent)
	
	enum { CONTROL_CHANGED = 0 };
	
	Vector3 sticker;
	float acceleration;
};

//******************************************************************************
//
//  TouchPlayerControllerGetDataEvent
//
//******************************************************************************

// Used for retrieving data from TouchPlayerController
class TouchPlayerControllerGetDataEvent : public Event {
public:
	GENERATE_EVENT_ID(TouchPlayerControllerGetDataEvent)
	
	Vector3 initialStickerPos;
	Vector3 currentStickerPos;
	float stickerRadius;
	bool stickerEnabled;
};

#endif
