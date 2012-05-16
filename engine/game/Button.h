//
//  Button.h
//  SurviveInSpace
//
//  Created by Nikita Sidorenko on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"

class SpriteRenderer;
class Texture;

class Button : public Component {
public:
    GENERATE_COMPONENT_ID(Button);
    
    Button();
    
    void SetTexture(const std::string &textureName);
    void SetTexture(const Texture *texture);
    
    virtual void Awake();
    
private:
    SpriteRenderer *_spriteRenderer;
    
    
};

#endif
