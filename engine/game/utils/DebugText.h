//
//  DebugText.h
//  SurviveInSpace
//
//  Created by Nikita on 5/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef DEBUG_TEXT_H
#define DEBUG_TEXT_H

#include "Component.h"

class TextRenderer;

class DebugText : public Component {
public:
	GENERATE_COMPONENT_ID(DebugText)
	
	virtual void Awake();
	
private:
	TextRenderer *_textRenderer;
	
};

#endif
