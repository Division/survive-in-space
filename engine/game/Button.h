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
#include "SpriteRenderer.h"

class Texture;

class Button : public Component {
public:
    GENERATE_COMPONENT_ID(Button);
    
    Button();
    
    void SetTexture(const std::string &textureName);
    void SetTexture(Texture *texture);
    
    void Size(const Vector2 &size) { _spriteRenderer->Size(size); };
    Vector2 Size() const { return _spriteRenderer->Size(); }
    
    void Position(const Vector2 &position) { _spriteRenderer->Position(position); };
    Vector2 Position() const { return _spriteRenderer->Position(); }

    class Material &Material() const { return _spriteRenderer->Material(); }
    void Material(class Material &material) { _spriteRenderer->Material(material); }
    
    virtual void Awake();
    
private:
    void ApplyState(bool down);
    
private:
    SpriteRenderer *_spriteRenderer;
    bool _isDown;
    
};

#endif
