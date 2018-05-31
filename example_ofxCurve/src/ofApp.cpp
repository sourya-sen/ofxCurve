#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Have a vector<glm::vec3> of control points. They must be 3n + 1 in number, otherwise the interpolations won't run.
    cps.push_back(glm::vec3(100.0, 150.0, 0.0));
    cps.push_back(glm::vec3(200.0, 200.0, 0.0));
    cps.push_back(glm::vec3(300.0, 650.0, 0.0));
    cps.push_back(glm::vec3(400.0, 400.0, 0.0));
    cps.push_back(glm::vec3(500.0, 450.0, 0.0));
    cps.push_back(glm::vec3(600.0, 222.0, 0.0));
    cps.push_back(glm::vec3(800.0, 150.0, 0.0));
    
    
    //Call the functions with a 'step' variable, which determines the density of interpolated points.
    pointsBezier = evalBezier(cps, 1000); //evalBezier interpolates a bezier curve
    pointsBSpline = evalBspline(cps, 1000); //evalBspline interpolates a BSpline
    pointsCR = evalCR(cps, 1000); //evalCR interpolates a Catmull-Rom spline
    
    ofSetBackgroundColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Visualizing the interpolated points.
    
    ofSetColor(0, 255, 0);
    for(int i = 0; i<pointsBezier.size(); i++){
        ofDrawCircle(pointsBezier[i], 2);
    }
    
    ofSetColor(255, 0, 0);
    for(int i = 0; i<pointsBSpline.size(); i++){
        ofDrawCircle(pointsBSpline[i], 2);
    }
    
    ofSetColor(0, 0, 255);
    for(int i = 0; i<pointsCR.size(); i++){
        ofDrawCircle(pointsCR[i], 2);
    }
    
    //The original control points.
    
    ofSetColor(255);
    for(int i = 0; i<cps.size(); i++){
        ofDrawCircle(cps[i], 5);
    }
    
    ofDrawBitmapString("Green: Bezier, Red: BSpline, Blue: Catmull-Rom, White: Original control points", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
