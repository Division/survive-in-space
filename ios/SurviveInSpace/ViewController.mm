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
    bool _initialized;
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

    _initialized = false;
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    [EAGLContext setCurrentContext:self.context];
    
    self.glview.context = self.context;
    self.glview.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
}

-(void) viewDidAppear:(BOOL)animated {
    
    [super viewDidAppear:animated];
    
	if (_initialized) return;
	
	_platform = new Platform_iOS((GameView *)self.view);
    _game = new Game();
    _game->Init(_platform);
    
    _initialized = true;
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
    gameView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
	gameView.multipleTouchEnabled = YES;
	self.view = gameView;
}


-(void) touchesChanged:(NSSet *)touches {
	
    _platform->ProcessChangedTouches(touches);
}


- (void)update {

    if (!_initialized) return;
    _game->Update(self.timeSinceLastUpdate);
    _platform->ClearTouchMessages();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {

    if (!_initialized) return;
    _game->Render(Vector4(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height));
}

@end
