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
#include "Button.h"

class TouchPlayerControllerGetDataEvent;
class SpriteRenderer;
class Event;

/**
 Rendering of in-game user interface
 Sticker control, speed buttons, labels etc
 Broadcasts button events
 */
class TouchGameUI : public Component, public ButtonDelegate {
public:
	GENERATE_COMPONENT_ID(TouchGameUI);
	
	//-------------------
	// Component
	virtual void Awake();
	virtual void Update();
	
	//-------------------
	// ButtonDelegate
    virtual void ButtonDown(Button *button);
    virtual void ButtonUp(Button *button);
    
private:
	void SetStickerEnabled(bool enabled);
    void ConfigureSticker(TouchPlayerControllerGetDataEvent *event);
    SpriteRenderer *CreateSprite(const std::string &texture, int renderQueue, Vector2 size, Vector2 position);
    Button *CreateButton(const std::string &texture, int RenderQueue, const Vector2 &size, const Vector2 &position, bool invertY);
    
private:
	SpriteRenderer *_stickerBackground;
	SpriteRenderer *_stickerButton;
	Button *_speedUpButton;
	Button *_speedDownButton;
    
    bool _speedUpButtonDown;
    bool _speedDownButtonDown;
};

#endif
