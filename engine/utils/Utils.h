//
//  Utils.h
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//

#ifndef Cpptest_Utils_h
#define Cpptest_Utils_h

#include <string>
#include "Platform.h"

namespace utils {
    
	void Update();
	
    bool GetResourcePath(const std::string& resourceName, std::string& outString);
    
    bool GetTextFileContents(const std::string& resourceName, std::string& outString);
    
    void Log(const std::string& message);
    
	bool IsRunningDevice();
	
	void Init(Platform *platform);
	
	double GetTime();
	
	double DeltaTime();
	
	unsigned long Hash(const std::string& string);
	
	Vector2 GetScreenResolution();
}

#endif
