//
// Created by otavio on 12/03/2021.
//

#include "Player.h"

void Player::initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color) {
    x = _x;
    y = _y;
    angle = _angle;
    head = new Circle(0, 0, _r, color);
    nose = new Circle(_r * 1.01, 0, _r * 0.2, color);
}

void Player::setArena(Arena *_arena) {
    arena = _arena;
}

void Player::draw() {
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    head->draw();
    nose->draw();

    glPopMatrix();
}

void Player::rotate(GLdouble deltaTime) {
    angle += deltaTime * ANGULAR_VELOCITY;
}

void Player::walk(GLdouble deltaTime) {
    double rad = Utils::degToRad(angle);
    x += deltaTime * LINEAR_VELOCITY * cos(rad);
    y += deltaTime * LINEAR_VELOCITY * sin(rad);
}

void Player::drawBarrier() {
    float piIncrement = 2 * M_PI / 18;
    float radius =

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_LINE);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 18; i++) {
        glVertex3f(radius * cos(piIncrement * i), radius * sin(piIncrement * i), 0);
    }
    glEnd();
    glPopMatrix();
}
