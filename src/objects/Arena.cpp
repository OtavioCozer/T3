//
// Created by otavio on 12/03/2021.
//

#include "Arena.h"
#include "../model/Image.h"

void Arena::initialize(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _height, GLfloat _width) {
    x = _x * ARENA_SCALE;
    y = _y * ARENA_SCALE;
    z = _z * ARENA_SCALE;
    height = _height * ARENA_SCALE;
    width = _width * ARENA_SCALE;
}


void Arena::initializeTexture() {
    printf("loading arena texture\n");
    textureFloor = loadTexture("../resources/AdvancedFloorInterlockingOld_basecolor.bmp");
    textureWall = loadTexture("../resources/MetalPipeWallRusty_basecolor.bmp");
}

GLuint Arena::loadTexture(const char *filename) {
    GLuint texture;

    Image *image = Image::loadImage(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
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

void Arena::draw() {
    drawRectangle(textureFloor, 0, 1, 0);

//    glPushMatrix();
//    glRotatef(-90, 1, 0, 0);
//    glTranslatef(0, -width, 0);
//    drawRectangle(textureWall);
//    glPopMatrix();
//
//    glPushMatrix();
//    glRotatef(-90, 1, 0, 0);
//    glRotatef(-90, 0, 0, 1);
//    drawRectangle(textureWall);
//    glPopMatrix();
//
//    glPushMatrix();
//    glRotatef(-90, 1, 0, 0);
//    drawRectangle(textureWall);
//    glPopMatrix();
//
//    glPushMatrix();
//    glRotatef(-90, 1, 0, 0);
//    drawRectangle(textureWall);
//    glPopMatrix();
//
//    glPushMatrix();
//    glRotatef(-90, 0, 0, 1);
//    drawRectangle(textureWall);
//    glPopMatrix();
}

void Arena::drawRectangle(GLuint texture, GLfloat xn, GLfloat yn, GLfloat zn) {
    GLfloat materialEmission[] = {0.1, 0.1, 0.2, 1};
    GLfloat materialColorA[] = {0.1, 0.1, 0.1, 1};
    GLfloat materialColorD[] = {5, 5, 5, 1};
    GLfloat mat_specular[] = {5, 5, 5, 1};
    GLfloat mat_shininess[] = {50.0};
    glColor3f(1, 1, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //Y

    glBindTexture(GL_TEXTURE_2D, texture);
    double textureS = 1;  // Bigger than 1, repeat
    int points = 4;

    for (unsigned int i = 0; i < points; i = i + 4) {
        glBegin(GL_QUAD_STRIP);
        for (unsigned int j = i; j < i + 4; j++) {
            glNormal3f(xn, yn, zn);
            glTexCoord2f(frame.vertsS[j].vTex.u, frame.vertsS[j].vTex.v);
            glVertex3f(frame.vertsS[j].vPos.x, frame.vertsS[j].vPos.y, frame.vertsS[j].vPos.z);
        }
        glEnd();
    }

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(x, 0, z);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0, textureS);
    glVertex3f(x, 0, z + height);

    glNormal3f(0, 1, 0);
    glTexCoord2f(textureS, textureS);
    glVertex3f(x + height, 0, z + width);

    glNormal3f(0, 1, 0);
    glTexCoord2f(textureS, 0);
    glVertex3f(x + height, 0, z);
    glEnd();
}

void Arena::getTexCoord(int j) {}

