//
// Created by otavio on 11/03/2021.
//

#ifndef T2_CIRCLE_H
#define T2_CIRCLE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

class Circle {
public:
    GLfloat cx;
    GLfloat cy;
    GLfloat r;
    GLfloat R;
    GLfloat G;
    GLfloat B;

    Circle();

    Circle(GLfloat _cx, GLfloat _cy, GLfloat _r, const std::string &color);

    void setColor(const std::string &color);

    void draw();
};


#endif //T2_CIRCLE_H
