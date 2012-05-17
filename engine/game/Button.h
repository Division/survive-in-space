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
#include "MyMath.h"

class Button;

class ButtonDelegate {
public:
    virtual void ButtonDown(Button *button) { /* empty */ }
    virtual void ButtonUp(Button *button) { /* empty */ }
    virtual void ButtonPress(Button *button) { /* empty */ }
};

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
    
    bool InvertX() const { return _invertX; }
    void InvertX(bool invert) { _invertX = invert; ApplyState(_isDown); }
    bool InvertY() const { return _invertY; }
    void InvertY(bool invert) { _invertY = invert; ApplyState(_isDown); }
    
    void Delegate(ButtonDelegate *delegate) { _delegate = delegate; }
    ButtonDelegate *Delegate() { return _delegate; }
    
    virtual void PreUpdate();
    virtual void Awake();
    
private:
    void ApplyState(bool down);
    math::Rect GetButtonRect();
    void ButtonPressed();
    void ButtonUp();
    void ButtonDown();
    
private:
    SpriteRenderer *_spriteRenderer;
    bool _isDown;
    Vector2 _tapAreaScale;
    int _touchID;
    ButtonDelegate *_delegate;
    bool _invertX;
    bool _invertY;
};

#endif
