//
//  GetData.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GetData.h"
#include "Resource.h"

namespace getdata {

	//******************************************************************************
	//
	//  Material
	//
	//******************************************************************************

	Material BasicMaterial(int renderQueue = RenderQueueGeometry, int blending = -1) {

		Material m;
		
		m.RenderQueue(renderQueue);
		if (blending >= 0) {
			m.Blending(true);
			m.SetBlendFunc((BlendFuncType)blending);
		}
		
		return m;
	}
	
	Material MaterialUnlitTexture(const std::string &texture, int renderQueue, int blending) {

		Material m = BasicMaterial(renderQueue, blending);
	
		m.Texture(resource::GetTexture(texture));
		m.Shader(resource::GetShader("SimpleShader"));
		
		return m;
	}


}