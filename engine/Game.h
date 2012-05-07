//
//  Game.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GAME_H
#define GAME_H

#include "MyMath.h"
#include "Platform.h"

class Game {
public:
    void Render(const Vector4& viewport);
    void Update(float deltaTime);
    void Init(Platform *platform);
    void Finalize();
};

#endif
