#include "ofxCurve.h"

//--------------------------------------------------------------------------------------
Curve coreBezier(glm::vec3 &p0,
                 glm::vec3 &p1,
                 glm::vec3 &p2,
                 glm::vec3 &p3,
                 unsigned steps) {
    
    Curve R(steps + 1);
    
    //Basis Matrix.
    glm::mat4 B;
    
    glm::vec4 x = glm::vec4(1, 0, 0, 0);
    glm::vec4 y =  glm::vec4(-3, 3, 0, 0);
    glm::vec4 z = glm::vec4(3, -6, 3, 0);
    glm::vec4 w = glm::vec4(-1, 3, -3, 1);
    
    
    B = glm::mat4(x, y, z, w);
    
    //Control Points;
    glm::mat4 controlPoints;
    
    glm::vec4 cx = glm::vec4(p0.x, p0.y, p0.z, 1);
    glm::vec4 cy = glm::vec4(p1.x, p1.y, p1.z, 1);
    glm::vec4 cz = glm::vec4(p2.x, p2.y, p2.z, 1);
    glm::vec4 cw = glm::vec4(p3.x, p3.y, p3.z, 1);
    
    controlPoints = glm::mat4(cx, cy, cz, cw);
    
    for (unsigned i = 0; i <= steps; ++i) {
        // ...
        float t = float(i)/float(steps);
        
        glm::vec4 tempVertex = controlPoints * B * glm::vec4(1, t, pow(t, 2), pow(t, 3));
        R[i] = glm::vec3(tempVertex);
        
    }
    
    
    return R;
}

//--------------------------------------------------------------------------------------
Curve evalBezier(vector<glm::vec3> &P, unsigned steps) {
    bool run;
    
    if (P.size() < 4 || P.size() % 3 != 1) {
        cout << "Error: evalBezier must be called with 3n + 1 control points" << endl;
        run = false;
    } else {
        run = true;
    }
    
    Curve bezier;
    
    if(run){
        for (unsigned i = 0; i < P.size() - 3; ++i) {
            Curve smallBez = coreBezier(P[3 * i], P[3 * i + 1], P[3 * i + 2], P[3 * i + 3], steps);
            bezier.insert(bezier.end(), smallBez.begin(), smallBez.end());
        }
    }
    
    return bezier;
}

//--------------------------------------------------------------------------------------
Curve evalBspline(vector<glm::vec3> &P, unsigned steps){
    bool run;
    
    if (P.size() < 4 || P.size() % 3 != 1) {
        cout << "Error: evalBspline must be called with 3n + 1 control points" << endl;
        run = false;
    } else {
        run = true;
    }
    
    Curve bSpline;
    
    if(run){
        for (unsigned i = 0; i < P.size() - 3; ++i) {
            
            //Control Points
            glm::mat4 cPoint;
            
            glm::vec4 cx = glm::vec4(P[i].x, P[i].y, P[i].z, 1);
            glm::vec4 cy = glm::vec4(P[i+1].x, P[i+1].y, P[i+1].z, 1);
            glm::vec4 cz = glm::vec4(P[i+2].x, P[i+2].y, P[i+2].z, 1);
            glm::vec4 cw = glm::vec4(P[i+3].x, P[i+3].y, P[i+3].z, 1);
            
            cPoint = glm::mat4(cx, cy, cz, cw);
            
            //Basis Matrix for Bspline
            glm::mat4 bSplineB;
            
            glm::vec4 basisbx = glm::vec4(1.0, 4.0, 1.0, 0.0);
            glm::vec4 basisby = glm::vec4(-3.0, 0.0, 3.0, 0.0);
            glm::vec4 basisbz = glm::vec4(3.0, -6.0, 3.0, 0.0);
            glm::vec4 basisbw = glm::vec4(-1.0, 3.0, -3.0, 1.0);
            
            bSplineB = glm::mat4(basisbx, basisby, basisbz, basisbw);
            
            bSplineB = bSplineB / float(6);
            
            //Basis Matrix of Bezier
            glm::mat4 B;
            
            glm::vec4 x = glm::vec4(1, 0, 0, 0);
            glm::vec4 y =  glm::vec4(-3, 3, 0, 0);
            glm::vec4 z = glm::vec4(3, -6, 3, 0);
            glm::vec4 w = glm::vec4(-1, 3, -3, 1);
            
            B = glm::mat4(x, y, z, w);
            
            //Matrix Conversion
            glm::mat4 newPointsM;
            
            newPointsM = cPoint * bSplineB * glm::inverse(B);
            
            glm::vec4 p0_4 = newPointsM[0];
            glm::vec4 p1_4 = newPointsM[1];
            glm::vec4 p2_4 = newPointsM[2];
            glm::vec4 p3_4 = newPointsM[3];
            
            glm::vec3 p0 = glm::vec3(p0_4);
            glm::vec3 p1 = glm::vec3(p1_4);
            glm::vec3 p2 = glm::vec3(p2_4);
            glm::vec3 p3 = glm::vec3(p3_4);
            
            vector<glm::vec3> newPoints;
            
            newPoints.push_back(p0); newPoints.push_back(p1); newPoints.push_back(p2); newPoints.push_back(p3);
            Curve smallbSpline = evalBezier(newPoints, steps);
            
            bSpline.insert(bSpline.end(), smallbSpline.begin(), smallbSpline.end());
        }
    }
    return bSpline;
}

//--------------------------------------------------------------------------------------
Curve evalCR(vector<glm::vec3> &P, unsigned steps){
    bool run;
    
    if (P.size() < 4 || P.size() % 3 != 1) {
        cout << "Error: evalCRmust be called with 3n + 1 control points" << endl;
        run = false;
    } else {
        run = true;
    }
    
    Curve Cr;
    
    if(run){
    for (unsigned i = 0; i < P.size()-1; ++i) {
        
        //Control Points
        glm::mat4 cPoint;
        
        glm::vec4 cx = glm::vec4(P[(i - 1) % P.size()].x, P[(i - 1) % P.size()].y, P[(i - 2) % P.size()].z, 1);
        glm::vec4 cy = glm::vec4(P[(i) % P.size()].x, P[(i) % P.size()].y, P[(i) % P.size()].z, 1);
        glm::vec4 cz = glm::vec4(P[(i + 1) % P.size()].x, P[(i + 1) % P.size()].y, P[(i + 1) % P.size()].z, 1);
        glm::vec4 cw = glm::vec4(P[(i + 2) % P.size()].x, P[(i + 2) % P.size()].y, P[(i + 2) % P.size()].z, 1);
        
        cPoint = glm::mat4(cx, cy, cz, cw);
        
        //Catmull-Rom Basis Matrix
        glm::mat4 CR;
       
        glm::vec4 crx = glm::vec4(0.0, 2.0, 0.0, 0.0);
        glm::vec4 cry = glm::vec4(-1.0, 0.0, 1.0, 0.0);
        glm::vec4 crz = glm::vec4(2.0, -5.0, 4.0, -1.0);
        glm::vec4 crw = glm::vec4(-1.0, 3.0, -3.0, 1.0);
        
        CR = glm::mat4(crx, cry, crz, crw);
        
        CR = CR / float(2);
        
        //Basis Matrix of Bezier
        glm::mat4 B;
        
        glm::vec4 x = glm::vec4(1, 0, 0, 0);
        glm::vec4 y =  glm::vec4(-3, 3, 0, 0);
        glm::vec4 z = glm::vec4(3, -6, 3, 0);
        glm::vec4 w = glm::vec4(-1, 3, -3, 1);
        
        B = glm::mat4(x, y, z, w);
        
        //Matrix Conversion
        glm::mat4 newPointsM;
        
        newPointsM = cPoint * CR * glm::inverse(B);
        
        glm::vec4 p0_4 = newPointsM[0];
        glm::vec4 p1_4 = newPointsM[1];
        glm::vec4 p2_4 = newPointsM[2];
        glm::vec4 p3_4 = newPointsM[3];
        
        glm::vec3 p0 = glm::vec3(p0_4);
        glm::vec3 p1 = glm::vec3(p1_4);
        glm::vec3 p2 = glm::vec3(p2_4);
        glm::vec3 p3 = glm::vec3(p3_4);
        
        vector<glm::vec3> newPoints;
        
        newPoints.push_back(p0); newPoints.push_back(p1); newPoints.push_back(p2); newPoints.push_back(p3);
        Curve smallCr = evalBezier(newPoints, steps);
        
        Cr.insert(Cr.end(), smallCr.begin(), smallCr.end());
    }
    }
    
    return Cr;
    
    
}

