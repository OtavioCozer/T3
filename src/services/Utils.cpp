//
// Created by otavio on 12/03/2021.
//

#include "Utils.h"

double Utils::degToRad(GLfloat deg) {
    return deg * (M_PI / 180);
}

double Utils::distance(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double Utils::magnitude(GLfloat x, GLfloat y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}
