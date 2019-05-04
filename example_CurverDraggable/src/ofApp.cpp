#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    //    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetFrameRate(60);
    ofBackground(32);
    
    //-
    
    c = 0; //selected type curve to show. 0 = all
    c_name = "ALL CURVES";
    SHOW_Bezier = true;
    SHOW_BSpline = true;
    SHOW_CRoll = true;
    
    //-
    
    draggable.setAuto(true);
    
    //--
    
    // CREATE AND INITIATE POINTS
    
    //-
    
    int distToH = 100;//some helpers
    int yH = ofGetHeight() / 2;
    
    //-
    
    pointsBezier.clear();
    pointsBSpline.clear();
    pointsCR.clear();
    
    //-
    
    if ( CREATE_CURVE_MODE_CLASSIC == 1 )
    {
        mode_name = "CREATE_CURVE_MODE_CLASSIC";
        
        // 3n + 1 control points
        
        // 7 points
        
        glm::vec3(p1);
        glm::vec3(p2);
        glm::vec3(p3);
        glm::vec3(p4);
        glm::vec3(p5);
        glm::vec3(p6);
        glm::vec3(p7);
        
        p1 = glm::vec3(100.0, yH, 0.0);
        p2 = glm::vec3(200.0, yH + distToH, 0.0);
        p3 = glm::vec3(300.0, yH - distToH, 0.0);
        p4 = glm::vec3(400.0, yH, 0.0);
        p5 = glm::vec3(500.0, yH - distToH, 0.0);
        p6 = glm::vec3(600.0, yH + distToH, 0.0);
        p7 = glm::vec3(800.0, yH, 0.0);
        
        draggable.addPoint(p1.x, p1.y);
        draggable.addPoint(p2.x, p2.y);
        draggable.addPoint(p3.x, p3.y);
        draggable.addPoint(p4.x, p4.y);
        draggable.addPoint(p5.x, p5.y);
        draggable.addPoint(p6.x, p6.y);
        draggable.addPoint(p7.x, p7.y);
        
        cps.clear();
        cps.push_back(glm::vec3(p1));
        cps.push_back(glm::vec3(p2));
        cps.push_back(glm::vec3(p3));
        cps.push_back(glm::vec3(p4));
        cps.push_back(glm::vec3(p5));
        cps.push_back(glm::vec3(p6));
        cps.push_back(glm::vec3(p7));
    }
    //--
    
    else if (CURVE_MODE_UNLIMITED == 1)
    {
        mode_name = "CURVE_MODE_UNLIMITED";
        
        // non 3n + 1 control points
        
        // 6 points & duplicated 1st and last one
        
        glm::vec3(p0);
        glm::vec3(p1);
        glm::vec3(p2);
        glm::vec3(p3);
        glm::vec3(p4);
        glm::vec3(p5);
        glm::vec3(p6);
        glm::vec3(p7);
        glm::vec3(p8);
        
        p0 = glm::vec3(100.0, yH, 0.0);
        p1 = glm::vec3(100.0, yH, 0.0);
        p2 = glm::vec3(200.0, yH + distToH, 0.0);
        p3 = glm::vec3(300.0, yH - distToH, 0.0);
        p4 = glm::vec3(400.0, yH, 0.0);
        p5 = glm::vec3(500.0, yH - distToH, 0.0);
        p6 = glm::vec3(600.0, yH + distToH, 0.0);
        p7 = glm::vec3(800.0, yH, 0.0);
        p8 = glm::vec3(800.0, yH, 0.0);
        
        draggable.addPoint(p0.x, p0.y);
        draggable.addPoint(p1.x, p1.y);
        draggable.addPoint(p2.x, p2.y);
        draggable.addPoint(p3.x, p3.y);
        draggable.addPoint(p4.x, p4.y);
        draggable.addPoint(p5.x, p5.y);
        draggable.addPoint(p6.x, p6.y);
        draggable.addPoint(p7.x, p7.y);
        draggable.addPoint(p8.x, p8.y);
        
        cps.clear();
        cps.push_back(glm::vec3(p0));
        cps.push_back(glm::vec3(p1));
        cps.push_back(glm::vec3(p2));
        cps.push_back(glm::vec3(p3));
        cps.push_back(glm::vec3(p4));
        cps.push_back(glm::vec3(p5));
        cps.push_back(glm::vec3(p6));
        cps.push_back(glm::vec3(p7));
        cps.push_back(glm::vec3(p8));
    }
    
    //--
    
    else if (CREATE_CURVE_MINIMAL == 1)
    {
        mode_name = "CREATE_CURVE_MINIMAL";
        
        // minimal curve should have 4
        
        glm::vec3(p0);
        glm::vec3(p1);
        glm::vec3(p2);
        glm::vec3(p3);
        
        p0 = glm::vec3(100.0, yH, 0.0);
        p1 = glm::vec3(300.0, yH + distToH, 0.0);
        p2 = glm::vec3(600.0, yH - distToH, 0.0);
        p3 = glm::vec3(800.0, yH, 0.0);
        
        draggable.addPoint(p0.x, p0.y);
        draggable.addPoint(p1.x, p1.y);
        draggable.addPoint(p2.x, p2.y);
        draggable.addPoint(p3.x, p3.y);
        
        cps.clear();
        cps.push_back(glm::vec3(p0));
        cps.push_back(glm::vec3(p1));
        cps.push_back(glm::vec3(p2));
        cps.push_back(glm::vec3(p3));
    }
    
    //--
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Visualizing the interpolated points.
    
    ofPushStyle();
    
    //-
    
    // select curve to show
    
    if (SHOW_Bezier)
    {
        ofSetColor(0, 255, 0);
        for(int i = 0; i<pointsBezier.size(); i++){
            ofDrawCircle(pointsBezier[i], bezP_radius);
        }
    }
    
    if (SHOW_BSpline)
    {
        ofSetColor(255, 0, 0);
        for(int i = 0; i<pointsBSpline.size(); i++){
            ofDrawCircle(pointsBSpline[i], bezP_radius);
        }
    }
    
    if (SHOW_CRoll)
    {
        ofSetColor(0, 0, 255);
        for(int i = 0; i<pointsCR.size(); i++){
            ofDrawCircle(pointsCR[i], bezP_radius);
        }
    }
    
    //-
    
    //The control points
    
    for(int i = 0; i<cps.size(); i++)
    {
        //-
        
        ofSetColor(255, 128);
        ofDrawCircle(cps[i], bezP_radius);
        
        //-
        
        // show point numbers id
        ofPoint pad;//show both if they are have the same position..
        if ((i == 0)||(i == cps.size()-1))
            pad.set(10, -10);
        else
            pad.set(10, 10);
        
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(i+1), cps[i] + pad);
        
        //-
    }
    
    string str;
    str += "MODE: " + ofToString(mode_name) + "\n\n";
    str += "PUSH ANY KEY TO CHANGE CURVE MODE\n\n";
    str += "CURRENT CURVE: " + ofToString(c_name) + "\n";
    str += "Green: Bezier\n";
    str += "Red: BSpline\n";
    str += "Blue: Catmull-Rom\n";
    ofDrawBitmapString(str, 10, 40);
    
    ofPopStyle();
    
    //--
    
    for (int i=0; i<draggable.size(); i++)
    {
        cps[i] = (glm::vec3(draggable.get(i)));
    }
    
    //-
    
    // Call the functions with a 'step' variable, which determines the density of interpolated points.
    
    if (SHOW_Bezier)
        pointsBezier = evalBezier(cps, reso); //evalBezier interpolates a bezier curve
    
    if (SHOW_BSpline)
        pointsBSpline = evalBspline(cps, reso); //evalBspline interpolates a BSpline
    
    if (SHOW_CRoll)
        pointsCR = evalCR(cps, reso); //evalCR interpolates a Catmull-Rom spline
    
    //--
    
    draggable.draw();
    ofDrawBitmapString("DRAG THE POINTS!", 10, 200);
    
    //--
    
    // white line start to end
    
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofDrawLine( cps[0], cps[cps.size()-1] );
    ofPopStyle();
    
    //-
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    c = (c + 1) % 4;
    
    if (c == 0) //show all curves
    {
        SHOW_Bezier = SHOW_BSpline = SHOW_CRoll = true;
        c_name = "ALL CURVES";
    }
    else if (c == 1)
    {
        SHOW_Bezier = true;
        SHOW_BSpline = SHOW_CRoll = false;
        c_name = "BEZIER";
    }
    else if (c == 2)
    {
        SHOW_BSpline = true;
        SHOW_Bezier = SHOW_CRoll = false;
        c_name = "BSPLINE";
    }
    else if (c == 3)
    {
        SHOW_CRoll = true;
        SHOW_BSpline = SHOW_Bezier = false;
        c_name = "CROLL";
    }
    
    
    
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
