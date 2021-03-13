//
// Created by otavio on 11/03/2021.
//

#include "Rectangle.h"


Rectangle::Rectangle() {}

Rectangle::Rectangle(GLfloat _height, GLfloat _width, GLfloat r, GLfloat g, GLfloat b) {
    height = _height;
    width = _width;
    R = r;
    G = g;
    B = b;
}

void Rectangle::draw() {
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
    glVertex3f(width / 2, height, 0);
    glVertex3f(-width / 2, height, 0);
    glVertex3f(-width / 2, 0, 0);
    glVertex3f(width / 2, 0, 0);
    glEnd();
}


