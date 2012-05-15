//
//  ViewController.m
//  Cpptest
//
//  Created by Nikita Sidorenko on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#include "Utils.h"
#include "Game.h"
#include "Input.h"
#include "Platform_iOS.h"

@interface ViewController() {
@private
    Game *_game;
    Platform_iOS *_platform;
}

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, readonly) GLKView *glview;

@end

@implementation ViewController

@synthesize context = _context;

-(GLKView *) glview {
    
    return (GLKView *)self.view;
}


#pragma mark - View lifecycle

-(BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {

	return UIInterfaceOrientationIsLandscape(toInterfaceOrientation);
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    [EAGLContext setCurrentContext:self.context];
    
    self.glview.context = self.context;
    self.glview.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
	_platform = new Platform_iOS();
    _game = new Game();
    _game->Init(_platform);
}

- (void)viewDidUnload
{
	[super viewDidUnload];

	_game->Finalize();
	delete _game;
	delete _platform;
}


- (void) loadView {

	GameView *gameView = [[GameView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	gameView.gameViewDelegate = self;
	self.view = gameView;
}


-(void) touchesChanged:(NSSet *)touches {
	
	NSArray *allObjects = [touches allObjects];
	input::TouchList touchList;
	
	for (UITouch *touch in allObjects) {
		CGPoint location = [touch locationInView:self.view];
		CGPoint prevLocation = [touch previousLocationInView:self.view];
		
		input::Touch gameTouch;
		gameTouch.position = Vector3(location.x, location.y, 0);
		gameTouch.prevPosition = Vector3(prevLocation.x, prevLocation.y, 0);
		
		switch (touch.phase) {
			case UITouchPhaseBegan:
				gameTouch.phase = platform::TouchPhaseBegan;
				break;

			case UITouchPhaseMoved:
				gameTouch.phase = platform::TouchPhaseMoved;
				break;
				
			case UITouchPhaseStationary:
				gameTouch.phase = platform::TouchPhaseStationary;
				break;

			case UITouchPhaseCancelled:
			case UITouchPhaseEnded:
				gameTouch.phase = platform::TouchPhaseEnd;
				break;
		}
		
		touchList.push_back(gameTouch);
	}
	
	_platform->SetTouches(touchList);
	_platform->TouchesChanged(true);
}


- (void)update {

    _game->Update(self.timeSinceLastUpdate);
	_platform->TouchesChanged(false);    
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {


    _game->Render(Vector4(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height));
}

@end
