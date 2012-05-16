//
//  GetData.h
//  SurviveInSpace
//
//  Created by Nikita on 5/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GET_DATA_H
#define GET_DATA_H

#include "Material.h"
#include <string>

namespace getdata {

	//******************************************************************************
	//
	//  Material
	//
	//******************************************************************************

	
	Material MaterialUnlitTexture(const std::string &texture, int renderQueue = RenderQueueGeometry, int blending = -1);

	Material MaterialGUI(const std::string &texture, int renderQueue);
}

#endif
