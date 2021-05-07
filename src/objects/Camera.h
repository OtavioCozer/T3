//
// Created by otavio on 05/05/2021.
//

#ifndef T3_CAMERA_H
#define T3_CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


class Camera {
public:
    GLdouble eyeX;
    GLdouble eyeY;
    GLdouble eyeZ;
    GLdouble centerX;
    GLdouble centerY;
    GLdouble centerZ;
    GLdouble upX;
    GLdouble upY;
    GLdouble upZ;
    GLdouble XYAngle;
    GLdouble XZAngle;
    int state;
    GLdouble r;

    void initialize(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz,
                    GLdouble upx, GLdouble upy, GLdouble upz, int _state);
};


#endif //T3_CAMERA_H
