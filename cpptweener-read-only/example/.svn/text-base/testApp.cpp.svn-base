#include "testApp.h"
#include "CppTweener.h"

tween::Tweener tweener;

float px;
float py;

float px2 ;
float py2 ;

float px3 = 400 ;
float py3 = 400;

float alpha;
float rotZ;

int duration ;
int step = 0;
int max_steps = 5;

float pwidth = 200;
float pheight = 200;

//Multiple tween
void createTween1() {
    px = 0;
    py = 10;

    px2 = 600;
    py2 = 10;

    alpha = 0;
    rotZ = 0;
    // 5 seconds
    tween::TweenerParam param(2000, tween::CUBIC, tween::EASE_OUT);
    param.addProperty(&px, 200);
    param.addProperty(&py, 30);
    param.addProperty(&px2, 400);
    param.addProperty(&py2, 30);
    param.addProperty(&alpha, 255);
    param.addProperty(&rotZ, 360);
    tweener.addTween(param);
}
//Animation Tween
void createTween2() {

    tween::TweenerParam param2(1000, tween::BOUNCE);
    switch (step) {
        case 0:
            param2.addProperty(&px, 0);
            param2.addProperty(&rotZ, 90);
            break;
        case 1:
            param2.addProperty(&py, ofGetHeight()-200);
            param2.addProperty(&rotZ, 180);
            break;
        case 2:
            param2.addProperty(&px, ofGetWidth()-200);
            param2.addProperty(&rotZ, 270);
            break;
        case 3:
            param2.addProperty(&py, 0);
            param2.addProperty(&rotZ, 360);
            break;
        case 4:
            param2.addProperty(&px, 600);
            param2.addProperty(&py, 30);
            param2.addProperty(&rotZ, 360);
            break;

    }
    if (step < max_steps) {
      tweener.addTween(param2);
      step++;
    }
}

void createTween3(){
     tween::TweenerParam param(4000, tween::ELASTIC);
     param.addProperty(&pwidth, 600);
     param.addProperty(&pheight, 600);
     param.addProperty(&px3, 200);
     param.addProperty(&py3, 200);
     param.addProperty(&alpha, 127);
     tweener.addTween(param);


}
//--------------------------------------------------------------
void testApp::setup(){
    cout<<"Iniciado";
    createTween1();
    tweener.addListener(this);
    duration = ofGetElapsedTimeMillis();
}

void testApp::onStart(TweenerParam& param){
        cout<<"\nComeçou tween";

    } ;
void testApp::onStep(TweenerParam& param) {
       // cout<<"\nStep:"<< param.timeCount <<"\n";
    };
void testApp::onComplete(TweenerParam& param){
        cout<<"\nTween complete in :"<< (ofGetElapsedTimeMillis() - duration) <<" millisecs!\n";
        duration = ofGetElapsedTimeMillis();

        if (step == max_steps) {
          tweener.removeListener(this);
          createTween3();
        } else {
           createTween2() ;
        }


};

//--------------------------------------------------------------
void testApp::update(){
    //You pass de timemillis :-)
    tweener.step(ofGetElapsedTimeMillis());
}

//--------------------------------------------------------------
void testApp::draw(){



    //white square
    ofSetColor(255,255,255);
    ofRect(px,py,200,200);

    //red square
    ofSetColor(255,0,0);
    ofRect(px2,py2,200,200);

    //black square
    ofEnableAlphaBlending();

     ofSetColor(0,0,0,alpha);
     glTranslated(px3,px3,0);
     glRotated(rotZ,0,0,1);
     ofRect(-100,-100,pwidth,pheight);

    ofDisableAlphaBlending();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

