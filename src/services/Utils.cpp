//
// Created by otavio on 12/03/2021.
//

#include "Utils.h"

double Utils::degToRad(GLfloat deg) {
    return deg * (M_PI / 180);
}

double Utils::radToDeg(GLfloat rad) {
    return rad * (180 / M_PI);
}


double Utils::distance(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double Utils::magnitude(GLfloat x, GLfloat y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Utils::translate(GLfloat &x, GLfloat &y, GLfloat tx, GLfloat ty) {
    x += tx;
    y += ty;
}

void Utils::rotate(GLfloat &x, GLfloat &y, GLfloat deg) {
    double rad = degToRad(deg);
    GLfloat tempox = x;
    GLfloat tempoy = y;

    x = tempox * cos(rad) - tempoy * sin(rad);
    y = tempox * sin(rad) + tempoy * cos(rad);
}