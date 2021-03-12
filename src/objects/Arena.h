//
// Created by otavio on 12/03/2021.
//

#ifndef T2_ARENA_H
#define T2_ARENA_H


#include "../polygons/Rectangle.h"

class Arena {
public:
    GLfloat x;
    GLfloat y;
    GLfloat height;
    GLfloat width;
    GLfloat R;
    GLfloat G;
    GLfloat B;

    void initializeArena(GLfloat _x, GLfloat _y, GLfloat _height, GLfloat _width, const std::string &color);
};


#endif //T2_ARENA_H
