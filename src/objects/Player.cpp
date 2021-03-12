//
// Created by otavio on 12/03/2021.
//

#include "Player.h"

GLfloat Player::getX() const {
    return x;
}

GLfloat Player::getY() const {
    return y;
}

GLfloat Player::getR() const {
    return head->r;
}

void Player::setArena(Arena *_arena) {
    arena = _arena;
}

void Player::initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color) {
    x = _x;
    y = _y;
    angle = _angle;
    head = new Circle(0, 0, _r, color);
    nose = new Circle(_r * 1.01, 0, _r * 0.2, color);
}

void Player::draw() {
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    head->draw();
    nose->draw();
    drawBarrier();

    glPopMatrix();
}

void Player::drawBarrier() {
    double piIncrement = 2 * M_PI / 36;
    double radius = getR() * BARRIER_SIZE_MULTIPLIER;

    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 36; i++) {
        glVertex3f(radius * cos(piIncrement * i), radius * sin(piIncrement * i), 0);
    }
    glEnd();
    glPopMatrix();
}

void Player::rotate(GLdouble deltaTime) {
    angle += deltaTime * ANGULAR_VELOCITY;
}

void Player::walk(GLdouble deltaTime, Player &player) {
    double rad = Utils::degToRad(angle);
    GLfloat xAfter = x + deltaTime * LINEAR_VELOCITY * cos(rad);
    GLfloat yAfter = y + deltaTime * LINEAR_VELOCITY * sin(rad);

    if(!checkPlayerCollision(xAfter, yAfter, player)) {
        x = xAfter;
        y = yAfter;
    }
}

bool Player::checkPlayerCollision(GLfloat _x, GLfloat _y, Player &player) {
    return Utils::distance(_x, _y, player.getX(), player.getY()) < getR() * BARRIER_SIZE_MULTIPLIER + player.getR();
}