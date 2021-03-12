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