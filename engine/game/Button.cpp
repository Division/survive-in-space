//
//  Button.cpp
//  SurviveInSpace
//
//  Created by Nikita Sidorenko on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Button.h"
#include "Resource.h"
#include "GameObject.h"
#include "GetData.h"
#include "Material.h"
#include "Input.h"

//******************************************************************************
//
//  Public
//
//******************************************************************************

Button::Button() {
    
    _spriteRenderer = NULL;
    _isDown = false;
    _tapAreaScale = Vector2(1, 1);
    _touchID = -1;
    _delegate = NULL;
    _invertX = false;
    _invertY = false;
}

//------------------------------------------------------------------------------

void Button::SetTexture(const std::string &textureName) {
    
    Texture *texture = resource::GetTexture(textureName);
    if (texture) {
        SetTexture(texture);
    }
}

//------------------------------------------------------------------------------

void Button::SetTexture(Texture *texture) {
    
    if (_spriteRenderer) {
        class Material m = _spriteRenderer->Material();
        _spriteRenderer->Material().Texture(texture);
    }
}

//------------------------------------------------------------------------------

void Button::PreUpdate() {
    
    math::Rect buttonRect = GetButtonRect();
    
    for (int messageID = 0; messageID < input::TouchMessageCount(); messageID++) {

        bool prevState = _isDown;
        bool stateToApply = _isDown;
        bool needUpdateState = false;
        
        for (int i = 0; i < input::TouchCount(messageID); i++) {
            
            input::Touch *touch = input::GetTouch(messageID, i);
            
            if (_isDown) { 
                // Button is currently down
                if (touch->id != _touchID) continue;
                
                bool touchInside = math::PointInRect(Vector2(touch->position), buttonRect);
                
                if (touch->phase == input::TouchPhaseEnd) {
                    // Touch Ended, check if we need to perform callback
                    _isDown = false;
                    stateToApply = _isDown;
                    needUpdateState = true;
                    _touchID = -1;

                    ButtonUp();
                    if (touchInside) {
                        ButtonPressed();
                    }
                    
                    break;
                } else {
                    // Touch is moving
                    stateToApply = touchInside;
                    needUpdateState = true;
                    prevState = false;
                    break;
                }
            } else {
                // Button is currently up
                if (math::PointInRect(Vector2(touch->position), buttonRect)) {
                    if (touch->phase == input::TouchPhaseBegan) {
                        _isDown = true;
                        stateToApply = _isDown;
                        needUpdateState = true;
                        _touchID = touch->id;
                        ButtonDown();
                    }
                }
            }
        }
        
        // Applying state
        needUpdateState = needUpdateState && (prevState ^ _isDown);
        if (needUpdateState) {
            ApplyState(stateToApply);
        }
    }
    

}

//------------------------------------------------------------------------------

void Button::Awake() {
    
    _spriteRenderer = GameObject()->AddComponent<SpriteRenderer>();
    _spriteRenderer->UseTransform(false);
    ApplyState(false);
}

//******************************************************************************
//
//  Private
//
//******************************************************************************

void Button::ApplyState(bool down) {
    
    Vector2 scale(1, 0.5);
    if (_invertX) scale.x *= -1;
    if (_invertY) scale.y *= -1;
    
    _spriteRenderer->UVScale(scale);

    Vector2 offset = Vector2(0,0.5);
    if (_invertY) down = !down;
    
    if (down) {
        offset.y = 0.0;
    }
    
    _spriteRenderer->UVOffset(offset);
}

//------------------------------------------------------------------------------

math::Rect Button::GetButtonRect() {
    
    Vector2 size = Size() * _tapAreaScale;
    return math::Rect(Position(), size);
}

//------------------------------------------------------------------------------

void Button::ButtonPressed() {
    
    if (_delegate) {
        _delegate->ButtonPress(this);
    }

	ButtonEvent buttonEvent(ButtonEvent::Press, this);
	DispatchEvent(&buttonEvent, EventDispatchUpwards);
}

//------------------------------------------------------------------------------

void Button::ButtonDown() {
    
    if (_delegate) {
        _delegate->ButtonDown(this);
    }
	
	ButtonEvent buttonEvent(ButtonEvent::Down, this);
	DispatchEvent(&buttonEvent, EventDispatchUpwards);
}

//------------------------------------------------------------------------------

void Button::ButtonUp() {
    
    if (_delegate) {
        _delegate->ButtonUp(this);
    }
	
	ButtonEvent buttonEvent(ButtonEvent::Up, this);
	DispatchEvent(&buttonEvent, EventDispatchUpwards);
}

