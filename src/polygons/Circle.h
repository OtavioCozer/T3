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
    GLfloat r;
    GLfloat R;
    GLfloat G;
    GLfloat B;

    Circle();

    Circle(GLfloat _r, const std::string &color);

    Circle(GLfloat _r, GLfloat r, GLfloat g, GLfloat b);

    void draw() const;
};


#endif //T2_CIRCLE_H
