//
// Created by otavio on 11/03/2021.
//

#include <cmath>
#include "Circle.h"

Circle::Circle() {

}

Circle::Circle(GLfloat _r, const std::string &color) {
    r = _r;

    R = color == "red";
    G = color == "green";
    B = color == "blue";
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
