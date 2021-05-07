//
// Created by otavio on 12/03/2021.
//

#include "Utils.h"
#include "../model/Image.h"

double Utils::degToRad(GLfloat deg) {
    return deg * (M_PI / 180);
}

double Utils::radToDeg(GLfloat rad) {
    return rad * (180 / M_PI);
}


double Utils::distance(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Utils::translate3(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat tx, GLfloat ty, GLfloat tz) {
    x += tx;
    y += ty;
    z += tz;
}

void Utils::rotate3(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat xv, GLfloat yv, GLfloat zv, GLfloat deg) {
    double rad = degToRad(deg);
    GLfloat tmpx = x;
    GLfloat tmpy = y;
    GLfloat tmpz = z;

    if (xv == 1 && yv == 0 && zv == 0) {
        x = tmpx * 1 + tmpy * 0 + tmpz * 0;
        y = tmpx * 0 + tmpy * cos(rad) - tmpz * sin(rad);
        z = tmpx * 0 + tmpy * sin(rad) + tmpz * cos(rad);
    } else if (xv == 0 && yv == 1 && zv == 0) {
        x = tmpx * cos(rad) + tmpy * 0 + tmpz * sin(rad);
        y = tmpx * 0 + tmpy * 1 + tmpz * 0;
        z = -tmpx * sin(rad) + tmpy * 0 + tmpz * cos(rad);
    } else if (xv == 0 && yv == 0 && zv == 1) {
        x = tmpx * cos(rad) - tmpy * sin(rad) + tmpz * 0;
        y = tmpx * sin(rad) + tmpy * cos(rad) + tmpz * 0;
        z = tmpx * 0 + tmpy * 0 + tmpz * 1;
    } else {
        perror("ROTATION NOT ALLOWED\n");
        exit(EXIT_FAILURE);
    }
}

void Utils::scale(GLfloat &x, GLfloat &y, GLfloat &z, GLfloat xf, GLfloat yf, GLfloat zf) {
    x *= xf;
    y *= yf;
    z *= zf;
}

GLuint Utils::loadTexture(const char *filename) {
    GLuint texture;

    Image *image = Image::loadImage(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB,                       //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,             //GL_UNSIGNED_BYTE, because pixels are stored
            //as unsigned numbers
                 image->pixels);               //The actual pixel data
    delete image;

    return texture;
}
