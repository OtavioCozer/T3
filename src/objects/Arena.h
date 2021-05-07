//
// Created by otavio on 12/03/2021.
//

#ifndef T2_ARENA_H
#define T2_ARENA_H

#define ARENA_SCALE 2

#include <GL/gl.h>
#include <GL/glut.h>
#include "3Definitions.h"

class Arena {
public:
    GLfloat x{};
    GLfloat y{};
    GLfloat z{};
    GLfloat height{};
    GLfloat width{};

    void initialize(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _height, GLfloat _width);

    void initializeTexture();

    void draw();

private:
    GLuint textureFloor{};
    GLuint textureWall{};
    GLfloat textureSpace{};
    GLfloat materialAmbient[4] = {0.1, 0.1, 0.1, 1};
    GLfloat materialDiffuse[4] = {5, 5, 5, 1};
    GLfloat materialSpecular[4] = {5, 5, 5, 1};
    GLfloat materialEmission[4] = {0.1, 0.1, 0.2, 1};
    GLfloat materialShininess[1] = {50.0};
    GLfloat color[4] = {1, 1, 1, 1};

    void drawRectangle(GLuint texture, norm n, GLfloat w, GLfloat h, int divide);

    void drawCube(GLuint texture, GLfloat size);
};


#endif //T2_ARENA_H
