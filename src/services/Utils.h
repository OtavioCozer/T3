//
// Created by otavio on 12/03/2021.
//

#ifndef T2_UTILS_H
#define T2_UTILS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class Utils {
public:
    static double degToRad(GLfloat deg);

    static double distance(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
};


#endif //T2_UTILS_H
