//
//  GameView.m
//  Cpptest
//
//  Created by Nikita on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GameView.h"

#import <UIKit/UIKit.h>

@implementation GameView

@synthesize gameViewDelegate = _gameViewDelegate;
@synthesize allTouches = _allTouches;


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {

	[super touchesBegan:touches withEvent:event];
	
	self.allTouches = [event allTouches];
	[self.gameViewDelegate touchesChanged:self.allTouches];
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {

	[super touchesMoved:touches withEvent:event];

	self.allTouches = [event allTouches];
	[self.gameViewDelegate touchesChanged:self.allTouches];
}


- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	
	[super touchesCancelled:touches withEvent:event];
	
	self.allTouches = [event allTouches];
	[self.gameViewDelegate touchesChanged:self.allTouches];
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	
	[super touchesEnded:touches withEvent:event];
	self.allTouches = [event allTouches];
	[self.gameViewDelegate touchesChanged:self.allTouches];
}

@end
