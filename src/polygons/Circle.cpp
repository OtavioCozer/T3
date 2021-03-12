//
// Created by otavio on 11/03/2021.
//

#include <cmath>
#include "Circle.h"

Circle::Circle() {

}

Circle::Circle(GLfloat _cx, GLfloat _cy, GLfloat _r, const std::string &color) {
    cx = _cx;
    cy = _cy;
    r = _r;

    if (color == "blue") {
        R = 0;
        G = 0;
        B = 1;
    } else if(color == "red") {
        R = 1;
        G = 0;
        B = 0;
    } else if(color == "green") {
        R = 0;
        G = 1;
        B = 0;
    }
}

void Circle::setColor(const std::string &color) {
    if (color == "blue") {
        R = 0;
        G = 0;
        B = 1;
    } else if(color == "red") {
        R = 1;
        G = 0;
        B = 0;
    } else if(color == "green") {
        R = 0;
        G = 1;
        B = 0;
    }
}

void Circle::draw() {
    double piIncrement = 2 * M_PI / 18;

    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glBegin(GL_POLYGON);
    glColor3f(R, G, B);
    for (int i = 0; i < 18; i++) {
        glVertex3f(r * cos(piIncrement * i), r * sin(piIncrement * i), 0);
    }
    glEnd();
    glPopMatrix();
}