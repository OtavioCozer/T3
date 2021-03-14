//
// Created by otavio on 13/03/2021.
//

#ifndef T2_MOUSE_H
#define T2_MOUSE_H

#include <GL/gl.h>
#include <GL/glu.h>

class Mouse {
public:
    GLfloat clickX;
    GLfloat clickY;

    GLfloat movedX;
    GLfloat movedY;

    int button;
    int state;

    Mouse();
};


#endif //T2_MOUSE_H
