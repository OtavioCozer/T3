//
// Created by otavio on 11/03/2021.
//

#ifndef T2_RECTANGLE_H
#define T2_RECTANGLE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>


class Rectangle {
public:
    GLfloat x;
    GLfloat y;
    GLfloat height;
    GLfloat width;
    GLfloat R;
    GLfloat G;
    GLfloat B;

    Rectangle();

    Rectangle(GLfloat _x, GLfloat _y, GLfloat _height, GLfloat _width, const std::string &color);

    void setColor(const std::string &color);

};


#endif //T2_RECTANGLE_H
