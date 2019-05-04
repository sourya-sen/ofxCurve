#pragma once

#include "ofMain.h"

#include "ofxCurve.h"
#include "ofxDraggable.h"

// TODO: must put only one of three modes to 1
#define CREATE_CURVE_MODE_CLASSIC 1
#define CURVE_MODE_UNLIMITED 0
#define CREATE_CURVE_MINIMAL 0

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    vector<glm::vec3> cps; //Control Points
    
    vector<glm::vec3> pointsBezier;
    vector<glm::vec3> pointsBSpline;
    vector<glm::vec3> pointsCR;

    //-

    bool SHOW_Bezier, SHOW_BSpline, SHOW_CRoll;
    int c;// 0 = show all
    string c_name;
    string mode_name;

    int reso = 500;//resolution of interpolation
    int bezP_radius = 1;//circle preview size

    //-

    int CURVE_MODE_DETECTED;

    //-
    
    ofxDraggable draggable;


};
