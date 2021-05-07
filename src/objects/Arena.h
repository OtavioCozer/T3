//
// Created by otavio on 12/03/2021.
//

#ifndef T2_ARENA_H
#define T2_ARENA_H

#define ARENA_SCALE 2

#include <GL/gl.h>
#include <GL/glut.h>

class Arena {
public:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat height;
    GLfloat width;
    GLuint textureFloor;
    GLuint textureWall;

    void initialize(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _height, GLfloat _width);

    void initializeTexture();

    GLuint loadTexture(const char *filename);

    void draw();

    void drawRectangle(GLuint texture, GLfloat xn, GLfloat yn, GLfloat zn);

    getTexCoord(int j);
};


#endif //T2_ARENA_H
