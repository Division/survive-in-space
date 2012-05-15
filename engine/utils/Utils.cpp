//
//  Utils.mm
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Utils.h"

static Platform *_platform;

namespace utils {

	double lastTime;
	
	void Update() {
		
		lastTime = GetTime();
	}
	
	//------------------------------------------------------------------------------
	
	bool GetResourcePath(const std::string& resourceName, std::string& outString) {
		
		return _platform->GetResourcePath(resourceName, outString);
	}

	//------------------------------------------------------------------------------
	
	bool GetTextFileContents(const std::string& resourceName, std::string& outString) {
		
		std::string path;
		
		bool result = false;
		
		if (GetResourcePath(resourceName, path)) {
			std::ifstream stream(path.c_str());
			try {
				stream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
				outString = std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
				result = true;
			} catch (std::exception e) {
				result = false;
			}
		}
		
		return result;
		
	}

	//------------------------------------------------------------------------------
	
	void Log(const std::string& message) {
		
		std::cout << message << std::endl;
	}
		
	//------------------------------------------------------------------------------
		
	bool IsRunningDevice() {
		
		bool runOnDevice = true;
		
		#if TARGET_IPHONE_SIMULATOR
		runOnDevice = false;
		#endif
		
		return runOnDevice;
	}
	
	//------------------------------------------------------------------------------
	
	void Init(Platform *thePlatform) {
		
		_platform = thePlatform;
		Update();
	}
	
	//------------------------------------------------------------------------------
	
	 double GetTime() {
		
		return _platform->GetTime();
	}
	
	//------------------------------------------------------------------------------
	
	double DeltaTime() {
		
		return GetTime() - lastTime;
	}
	
	//------------------------------------------------------------------------------
	
    unsigned long Hash(const std::string& string) {
		
		unsigned char *str = (unsigned char *)string.c_str();
        unsigned long hash = 5381;
        int c = *str;
		
        while (c) {
            hash = ((hash << 5) + hash) + c;
			c = *(++str);
		}
		
        return hash;
    }
	
	//------------------------------------------------------------------------------
	
	Vector2 GetScreenResolution() {
		
		return _platform->GetScreenResolution();
	}

	//------------------------------------------------------------------------------
	
	Vector2 GetInputResolution() {
		
		return _platform->GetInputResolution();
	}
}