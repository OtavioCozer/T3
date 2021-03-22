//
// Created by otavio on 12/03/2021.
//

#ifndef T2_UTILS_H
#define T2_UTILS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cmath>

class Utils {
public:
    static double degToRad(GLfloat deg);

    static double radToDeg(GLfloat rad);

    static double distance(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

    static double magnitude(GLfloat x, GLfloat y);

    static void translate(GLfloat &x, GLfloat &y, GLfloat tx, GLfloat ty);

    static void rotate(GLfloat &x, GLfloat &y, GLfloat deg);
};


#endif //T2_UTILS_H
