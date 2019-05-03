#pragma once
#include "ofMain.h"

typedef vector<glm::vec3> Curve;

Curve evalBezier(vector<glm::vec3> &P, unsigned steps);

Curve evalBspline(vector<glm::vec3> &P, unsigned steps);

Curve evalCR(vector<glm::vec3> &P, unsigned steps);


enum CURVE_MODE {
    CURVE_MODE_CLASSIC,
    CURVE_MODE_UNLIMITED
};


