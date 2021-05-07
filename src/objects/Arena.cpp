//
// Created by otavio on 12/03/2021.
//

#include "Arena.h"
#include "../model/Image.h"
#include "../services/Utils.h"

void Arena::initialize(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _height, GLfloat _width) {
    x = _x * ARENA_SCALE;
    y = _y * ARENA_SCALE;
    z = _z * ARENA_SCALE;
    height = _height * ARENA_SCALE;
    width = _width * ARENA_SCALE;
}


void Arena::initializeTexture() {
    printf("loading arena texture\n");
    textureFloor = Utils::loadTexture("../resources/AdvancedFloorInterlockingOld_basecolor.bmp");
    textureWall = Utils::loadTexture("../resources/MetalPipeWallRusty_basecolor.bmp");
}

void Arena::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);

    drawRectangle(textureFloor, {0, 1, 0}, width, height, 100);

    glPopMatrix();
}

void Arena::drawRectangle(GLuint texture, norm n, GLfloat w, GLfloat h, int divide) {
    glColor3f(color[0], color[1], color[2]);

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //Y

    glBindTexture(GL_TEXTURE_2D, texture);
    double textureS = (double)  3 / divide;  // Bigger than 1, repeat
    GLfloat wp = width / (GLfloat) divide;
    GLfloat hp = width / (GLfloat) divide;

    for (int i = 0; i < divide; i++) {
        for (int j = 0; j < divide; j++) {
            glBegin(GL_QUADS);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f(j * textureS, i * textureS);
            glVertex3f((GLfloat) j * wp, 0, (GLfloat) i * hp);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f(j * textureS, (i + 1) * textureS);
            glVertex3f((GLfloat) j * wp, 0, (GLfloat) (i + 1) * hp);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f((j + 1) * textureS, (i + 1) * textureS);
            glVertex3f((GLfloat) (j + 1) * wp, 0, (GLfloat) (i + 1) * hp);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f((j + 1) * textureS, i * textureS);
            glVertex3f((GLfloat) (j + 1) * wp, 0, (GLfloat) i * hp);

            glEnd();
        }
    }
}
