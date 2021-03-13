//
// Created by otavio on 11/03/2021.
//

#include <cmath>
#include "Circle.h"

Circle::Circle() {

}

Circle::Circle(GLfloat _r, const std::string &color) {
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

void Circle::draw() const {
    double piIncrement = 2 * M_PI / 18;

    glBegin(GL_POLYGON);
    glColor3f(R, G, B);
    for (int i = 0; i < 18; i++) {
        glVertex3f(r * cos(piIncrement * i), r * sin(piIncrement * i), 0);
    }
    glEnd();
}

Circle::Circle(GLfloat _r, GLfloat r, GLfloat g, GLfloat b) {
    Circle::r = _r;
    R = r;
    G = g;
    B = b;
};
