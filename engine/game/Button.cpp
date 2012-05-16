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

//******************************************************************************
//
//  Public
//
//******************************************************************************

Button::Button() {
    
    _spriteRenderer = NULL;
    _isDown = false;
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
    
    _isDown = down;

    _spriteRenderer->UVScale(Vector2(1,0.5));

    Vector2 offset = Vector2(0,0);
    if (down) {
        offset.y = 0.5;
    }
    
    _spriteRenderer->UVOffset(offset);
}
