[![Build status](https://travis-ci.org/sourya-sen/ofxCurve.svg?branch=master)](https://travis-ci.org/sourya-sen/ofxCurve)

openFrameworks addon for generating interpolated points on a curve based on a set of control points.

//--

ADDED TO ADDON CLASS: 
improved not 'always compliant to 3n+1 amount of points' from Sam McElhinney:
https://forum.openframeworks.cc/t/ofxcurve-addon-to-interpolate-curves-from-a-set-of-control-points/29645/2

ADDED EXAMPLE
+ "/example_CurverDraggable/" 
requires https://github.com/genekogan/ofxDraggable
to edit and drag curve points by mouse.

![ofxCurve](screenshots/ofxCurve2.png)

//--

Currently it can generate [Beziers](https://en.wikipedia.org/wiki/Bézier_curve), [B-Splines](https://en.wikipedia.org/wiki/B-spline) and [Catmull-Rom Splines](https://en.wikipedia.org/wiki/Centripetal_Catmull–Rom_spline). All of them are cubic.

These need to be fed a `vector<glm::vec3>` of control points and the number of points must be `3n + 1` in number.

![ofxCurve](screenshots/ofxCurve.png)
