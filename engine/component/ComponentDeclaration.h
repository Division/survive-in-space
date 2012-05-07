//
//  ComponentDeclaration.h
//  Cpptest
//
//  Created by Nikita on 4/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef COMPONENT_DECLARATION_H
#define COMPONENT_DECLARATION_H
#include "Physics.h"

#include "Transform.h"
class Transform;

#include "MeshRenderer.h"
class MeshRenderer;

#include "Camera.h"
class Camera;

#ifdef ENABLE_PHYSICS
#include "Rigidbody.h"
class Rigidbody;
#endif

#endif
