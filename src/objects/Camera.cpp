//
// Created by otavio on 05/05/2021.
//

#include "Camera.h"

void
Camera::initialize(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx, GLdouble centery, GLdouble centerz,
                   GLdouble upx, GLdouble upy, GLdouble upz, int _state) {
    eyeX = eyex;
    eyeY = eyey;
    eyeZ = eyez;
    centerX = centerx;
    centerY = centery;
    centerZ = centerz;
    upX = upx;
    upY = upy;
    upZ = upz;
    state = _state;
}
