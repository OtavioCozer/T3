//
// Created by otavio on 11/03/2021.
//

#include "Rectangle.h"


Rectangle::Rectangle() {}

Rectangle::Rectangle(GLfloat _x, GLfloat _y, GLfloat _height, GLfloat _width, const std::string &color) {
    x = _x;
    y = _y;
    height = _height;
    width = _width;

    if (color == "blue") {
        R = 0;
        G = 0;
        B = 1;
    } else if (color == "red") {
        R = 1;
        G = 0;
        B = 0;
    } else if (color == "green") {
        R = 0;
        G = 1;
        B = 0;
    }
}

Rectangle::Rectangle(GLfloat _x, GLfloat _y, GLfloat _height, GLfloat _width, GLfloat r, GLfloat g, GLfloat b,
                     GLfloat _angle) {
    x = _x;
    y = _y;
    angle = _angle;
    height = _height;
    width = _width;
    R = r;
    G = g;
    B = b;
}

void Rectangle::draw() {
    glColor3f(R, G, B);

    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(width / 2, height, 0);
    glVertex3f(-width / 2, height, 0);
    glVertex3f(-width / 2, 0, 0);
    glVertex3f(width / 2, 0, 0);
    glEnd();

    glPopMatrix();
}


void Rectangle::setColor(const std::string &color) {
    if (color == "blue") {
        R = 0;
        G = 0;
        B = 1;
    } else if (color == "red") {
        R = 1;
        G = 0;
        B = 0;
    } else if (color == "green") {
        R = 0;
        G = 1;
        B = 0;
    }
}