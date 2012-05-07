
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@protocol GameViewDelegate

-(void) touchesChanged:(NSSet *)touches;

@end

@interface GameView : GLKView

@property (nonatomic, retain) NSSet * allTouches;
@property (nonatomic, assign) id<GameViewDelegate> gameViewDelegate;

@end
