//
//  GameUI.h
//  SurviveInSpace
//
//  Created by Nikita on 5/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GAME_UI_H
#define GAME_UI_H

#include "Component.h"

class SpriteRenderer;

/**
 Rendering of in-game user interface
 Sticker control, speed buttons, labels etc
 */
class GameUI : public Component {
public:
	GENERATE_COMPONENT_ID(GameUI);
	
	//-------------------
	// Component
	virtual void Awake();
	virtual void Update();
	virtual void PreRender();
	
private:
	
private:
	SpriteRenderer *_stickerBackground;
	SpriteRenderer *_stickerButton;
	
};

#endif
