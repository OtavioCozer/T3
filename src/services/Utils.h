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

    static void translate3(GLfloat &y, GLfloat &x, GLfloat &z, GLfloat tx, GLfloat ty, GLfloat tz);

    static void rotate3(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat xv, GLfloat yv, GLfloat zv, GLfloat deg);

    static void scale(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat xf, GLfloat yf, GLfloat zf);

    static GLuint loadTexture(const char *filename);
};

#endif //T2_UTILS_H
