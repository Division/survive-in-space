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

Button::Button() {
    
    _spriteRenderer = NULL;
}

void Button::SetTexture(const std::string &textureName) {
    
    Texture *texture = resource::GetTexture(textureName);
    if (texture) {
        SetTexture(texture);
    }
}


void Button::SetTexture(const Texture *texture) {
    
    if (_spriteRenderer) {
        _spriteRenderer->SetTexture(texture);
    }
}


void Button::Awake() {
    
    _spriteRenderer = GameObject()->AddComponent<SpriteRenderer>();
}