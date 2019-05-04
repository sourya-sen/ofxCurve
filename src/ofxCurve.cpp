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
    int CURVE_MODE_DETECTED;

    //--

    // check number of points

    if (P.size() < 4 || P.size() % 3 != 1)
    {
        ofLogVerbose() << "detected CURVE_MODE_UNLIMITED: evalBezier is not called with 3n + 1 control points" ;// run = false;
        CURVE_MODE_DETECTED = CURVE_MODE_UNLIMITED;
    }
    else
    {
        ofLogVerbose() << "detected CURVE_MODE_CLASSIC: evalBezier is called with 3n + 1 control points" ;
        // run = true;
        CURVE_MODE_DETECTED = CURVE_MODE_CLASSIC;
    }

    run = true;//forced

    //--

    Curve bezier;
    
    if (run)
    {
        for (unsigned i = 0; i < P.size() - 3; ++i) {

            Curve smallBez;

            if (CURVE_MODE_DETECTED == CURVE_MODE_UNLIMITED)
            {
                int j = 3*i;
                int k = 3*i+1; if(k > P.size()-1) k = j;
                int m = 3*i+2; if(m > P.size()-1) m = k;
                int n = 3*i+3; if(n > P.size()-1) n = m;
                smallBez = coreBezier(P[j], P[k], P[m], P[n], steps);
            }

            //-

            else if (CURVE_MODE_DETECTED == CURVE_MODE_CLASSIC)
            {
                smallBez = coreBezier(P[3 * i], P[3 * i + 1], P[3 * i + 2], P[3 * i + 3], steps);
            }

            //-

            bezier.insert(bezier.end(), smallBez.begin(), smallBez.end());
        }
    }
    
    return bezier;
}

//--------------------------------------------------------------------------------------
Curve evalBspline(vector<glm::vec3> &P, unsigned steps){
    bool run;
    int CURVE_MODE_DETECTED;

    //--

    // check number of points

    if (P.size() < 4 || P.size() % 3 != 1)
    {
        ofLogVerbose() << "detected CURVE_MODE_UNLIMITED: evalBezier is not called with 3n + 1 control points" ;// run = false;
        CURVE_MODE_DETECTED = CURVE_MODE_UNLIMITED;
    }
    else
    {
        ofLogVerbose() << "detected CURVE_MODE_CLASSIC: evalBezier is called with 3n + 1 control points" ;
        // run = true;
        CURVE_MODE_DETECTED = CURVE_MODE_CLASSIC;
    }

    run = true;//forced

    //--

    Curve bSpline;
    
    if(run){
        for (unsigned i = 0; i < P.size() - 3; ++i) {
            
            //Control Points
            glm::mat4 cPoint;

            //--

            Curve smallBez;
            glm::vec4 cx;
            glm::vec4 cy;
            glm::vec4 cz;
            glm::vec4 cw;

            if (CURVE_MODE_DETECTED == CURVE_MODE_UNLIMITED)
            {
                int j = i;
                int k = i+1; if(k > P.size()-1) k = j;
                int m = i+2; if(m > P.size()-1) m = k;
                int n = i+3; if(n > P.size()-1) n = m;

                cx = glm::vec4(P[j].x, P[j].y, P[j].z, 1);
                cy = glm::vec4(P[j+1].x, P[j+1].y, P[j+1].z, 1);
                cz = glm::vec4(P[j+2].x, P[j+2].y, P[j+2].z, 1);
                cw = glm::vec4(P[j+3].x, P[j+3].y, P[j+3].z, 1);
            }

            //-

            else if (CURVE_MODE_DETECTED == CURVE_MODE_CLASSIC)
            {
                cx = glm::vec4(P[i].x, P[i].y, P[i].z, 1);
                cy = glm::vec4(P[i+1].x, P[i+1].y, P[i+1].z, 1);
                cz = glm::vec4(P[i+2].x, P[i+2].y, P[i+2].z, 1);
                cw = glm::vec4(P[i+3].x, P[i+3].y, P[i+3].z, 1);
            }

            //--

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
    int CURVE_MODE_DETECTED;

    //--

    // check number of points

    if (P.size() < 4 || P.size() % 3 != 1)
    {
        ofLogVerbose() << "detected CURVE_MODE_UNLIMITED: evalBezier is not called with 3n + 1 control points" ;// run = false;
        CURVE_MODE_DETECTED = CURVE_MODE_UNLIMITED;
    }
    else
    {
        ofLogVerbose() << "detected CURVE_MODE_CLASSIC: evalBezier is called with 3n + 1 control points" ;
        // run = true;
        CURVE_MODE_DETECTED = CURVE_MODE_CLASSIC;
    }

    run = true;//forced

    //--

    Curve Cr;
    glm::vec4 cx;
    glm::vec4 cy;
    glm::vec4 cz;
    glm::vec4 cw;

    //-

    if(run){
    for (unsigned i = 0; i < P.size()-1; ++i) {
        
        //Control Points
        glm::mat4 cPoint;

        //--

        if (CURVE_MODE_DETECTED == CURVE_MODE_UNLIMITED)
        {
            int h = (i-2) % P.size();   if(h < 0) h = 0;
            int j = (i-1) % P.size();   if(j < 0) j = 0;
            int k = (i) % P.size();     if(k > P.size()-1) k = j;
            int m = (i+1) % P.size();   if(m > P.size()-1) m = k;
            int n = (i+2) % P.size();   if(n > P.size()-1) n = m;

            cx = glm::vec4(P[j].x, P[j].y, P[h].z, 1);   //etc
            cy = glm::vec4(P[(j) % P.size()].x, P[(j) % P.size()].y, P[(j) % P.size()].z, 1);
            cz = glm::vec4(P[(j + 1) % P.size()].x, P[(j + 1) % P.size()].y, P[(j + 1) % P.size()].z, 1);
            cw = glm::vec4(P[(j + 2) % P.size()].x, P[(j + 2) % P.size()].y, P[(j + 2) % P.size()].z, 1);
        }

        //--

        else if (CURVE_MODE_DETECTED == CURVE_MODE_CLASSIC)
        {
            cx = glm::vec4(P[(i - 1) % P.size()].x, P[(i - 1) % P.size()].y, P[(i - 2) % P.size()].z, 1);
            cy = glm::vec4(P[(i) % P.size()].x, P[(i) % P.size()].y, P[(i) % P.size()].z, 1);
            cz = glm::vec4(P[(i + 1) % P.size()].x, P[(i + 1) % P.size()].y, P[(i + 1) % P.size()].z, 1);
            cw = glm::vec4(P[(i + 2) % P.size()].x, P[(i + 2) % P.size()].y, P[(i + 2) % P.size()].z, 1);
        }

        //--

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

