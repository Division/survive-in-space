//
//  MotionListener.h
//  SurviveInSpace
//
//  Created by Nikita on 5/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <CoreMotion/CoreMotion.h>

@interface MotionMonitor : NSObject

-(id) init;

@property (nonatomic, readonly) BOOL gyroAvailable;
@property (nonatomic, readonly) BOOL accelerometerAvailable;
@property (nonatomic, readonly) CMAccelerometerData *accelerometerData;
@property (nonatomic, readonly) CMGyroData *gyroData;

@end
