//
// Created by otavio on 12/03/2021.
//

#include "Arena.h"
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
    textureSpace = Utils::loadTexture("../resources/seamless_space.bmp");
}

void Arena::draw() {
    glColor3f(color[0], color[1], color[2]);

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //Y

    glPushMatrix();
    glTranslatef(x, y, z);

    drawRectangle(textureFloor, {0, 1, 0}, width, height, 100);

    glPushMatrix();
    glTranslatef(x/2, y/2, z/2);
    drawCube(textureSpace, height * 2);
    glPopMatrix();

    glPopMatrix();
}

void Arena::drawRectangle(GLuint texture, norm n, GLfloat w, GLfloat h, int divide) {
    glBindTexture(GL_TEXTURE_2D, texture);
    GLfloat textureS = (GLfloat) 3 / divide;  // Bigger than 1, repeat
    GLfloat wp = w / (GLfloat) divide;
    GLfloat hp = h / (GLfloat) divide;

    for (int i = 0; i < divide; i++) {
        for (int j = 0; j < divide; j++) {
            glBegin(GL_QUADS);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f((GLfloat) j * textureS, (GLfloat) i * textureS);
            glVertex3f((GLfloat) j * wp, 0, (GLfloat) i * hp);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f((GLfloat) j * textureS, (GLfloat) (i + 1) * textureS);
            glVertex3f((GLfloat) j * wp, 0, (GLfloat) (i + 1) * hp);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f((GLfloat) (j + 1) * textureS, (GLfloat) (i + 1) * textureS);
            glVertex3f((GLfloat) (j + 1) * wp, 0, (GLfloat) (i + 1) * hp);

            glNormal3f(n.x, n.y, n.z);
            glTexCoord2f((GLfloat) (j + 1) * textureS, (GLfloat) i * textureS);
            glVertex3f((GLfloat) (j + 1) * wp, 0, (GLfloat) i * hp);

            glEnd();
        }
    }
}

void Arena::drawCube(GLuint texture, GLfloat size) {
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    for(int i = 0; i < 3; i++) {
        if(i == 1) {
            glRotatef(90, 1, 0, 0);
        } else if(i == 2) {
            glRotatef(90, 0, 0, 1);
        }
        glBegin(GL_QUADS);
// ---------------- FACE 1 ------------------------------
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-size, -size, -size);

        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 1);
        glVertex3f(-size, -size, +size);

        glNormal3f(0, 1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(+size, -size, +size);

        glNormal3f(0, 1, 0);
        glTexCoord2f(1, 0);
        glVertex3f(+size, -size, -size);

// ---------------- FACE 2 ------------------------------
        glNormal3f(0, -1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-size, +size, -size);

        glNormal3f(0, -1, 0);
        glTexCoord2f(0, 1);
        glVertex3f(-size, +size, +size);

        glNormal3f(0, -1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(+size, +size, +size);

        glNormal3f(0, -1, 0);
        glTexCoord2f(1, 0);
        glVertex3f(+size, +size, -size);

        glEnd();
    }

    glPopMatrix();
    glEnable(GL_LIGHTING);
}
