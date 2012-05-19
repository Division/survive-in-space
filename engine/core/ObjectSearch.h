//
//  ObjectSearch.h
//  SurviveInSpace
//
//  Created by Nikita Sidorenko on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef OBJECT_SEARCH_H
#define OBJECT_SEARCH_H

#include <string>

class GameObject;

/*
 Interface for GameObject searching
 Scene and GameObject implement it
 */
class ObjectSearch {
public:

    virtual GameObject *SearchGameObject(const std::string &objectName) = 0;
    
};

#endif
