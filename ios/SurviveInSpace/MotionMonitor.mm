//
//  MotionListener.m
//  SurviveInSpace
//
//  Created by Nikita on 5/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MotionMonitor.h"

@interface MotionMonitor() 

@property (nonatomic, retain) CMMotionManager *motionManager;
@property (nonatomic, assign) BOOL gyroAvailable;
@property (nonatomic, assign) BOOL accelerometerAvailable;


@end

@implementation MotionMonitor

@synthesize motionManager = _motionManager;
@synthesize gyroAvailable = _gyroAvailable;
@synthesize accelerometerAvailable = _accelerometerAvailable;

-(id) init {

	if (self = [super init]) {
		
		self.motionManager = [[[CMMotionManager alloc] init] autorelease];
		self.gyroAvailable = self.motionManager.gyroAvailable;
		self.accelerometerAvailable = self.motionManager.accelerometerAvailable;
		
		if (self.gyroAvailable) {
			[self.motionManager startGyroUpdates];
		}
		
		if (self.accelerometerAvailable) {
			[self.motionManager startAccelerometerUpdates];
			self.motionManager.accelerometerUpdateInterval = 1.0f/30.0f;
		}
		
	}
	
	return self;
}
	

-(CMAccelerometerData *) accelerometerData {
	
	return self.motionManager.accelerometerData;
}


-(CMGyroData *) gyroData {
	
	return self.motionManager.gyroData;
}

@end
