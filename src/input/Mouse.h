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

    bool increasing;
    bool justClicked;

    int button;
    int state;
};


#endif //T2_MOUSE_H
