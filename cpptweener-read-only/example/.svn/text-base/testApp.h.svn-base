#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "CppTweener.h"
using namespace tween;
class testApp : public ofBaseApp, public tween::TweenerListener{


	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		void onStart(TweenerParam& param) ;
        void onStep(TweenerParam& param) ;
        void onComplete(TweenerParam& param);


};

#endif
