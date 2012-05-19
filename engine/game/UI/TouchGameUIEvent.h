//
//  GameUIEvent.h
//  SurviveInSpace
//
//  Created by Nikita on 5/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GAME_UI_EVENT_H
#define GAME_UI_EVENT_H

#include "Event.h"

class TouchGameUIButtonEvent : public Event {
public:
	GENERATE_EVENT_ID(TouchGameUIButtonEvent)
	
	bool speedUp;
	bool speedDown;
	bool firePressed;
	
};

#endif
