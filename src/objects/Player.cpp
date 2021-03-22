//
// Created by otavio on 12/03/2021.
//

#include <GL/glut.h>
#include "Player.h"

GLfloat Player::getX() const {
    return x;
}

GLfloat Player::getY() const {
    return y;
}

GLfloat Player::getHandSize() const {
    return head->r * HAND_SIZE_MULTIPLIER;
}

GLfloat Player::getR() const {
    return head->r;
}


GLfloat Player::getBarrier() const {
    return getR() * BARRIER_SIZE_MULTIPLIER;
}

void Player::setAngle(GLfloat _angle) {
    angle = _angle;
}

int Player::getScore() const {
    return score;
}

void Player::initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color) {
    x = _x;
    y = _y;
    angle = _angle;

    score = 0;
    bypassMouse = false;

    noseX = _r * NOSE_DISTANCE_MULTIPLIER;
    noseY = 0;

    head = new Circle(_r, color);
    nose = new Circle(_r * NOSE_SIZE_MULTIPLIER, color);


    leftArmX = 0;
    leftArmY = +_r;
    leftArmAngle = 30;

    rightArmX = 0;
    rightArmY = -_r;
    rightArmAngle = 150;

    leftArm = new Rectangle(_r * ARM_LENGTH_MULTIPLIER, _r * ARM_WIDTH_MULTIPLIER, (GLfloat) 153 / 255,
                            (GLfloat) 204 / 255, (GLfloat) 50 / 255);
    rightArm = new Rectangle(_r * ARM_LENGTH_MULTIPLIER, _r * ARM_WIDTH_MULTIPLIER, (GLfloat) 153 / 255,
                             (GLfloat) 204 / 255, (GLfloat) 50 / 255);

    leftForearmX = 0;
    leftForearmY = _r * ARM_LENGTH_MULTIPLIER;
    leftForearmAngle = -110;
    leftArmRotation = 0;

    rightForearmX = 0;
    rightForearmY = _r * ARM_LENGTH_MULTIPLIER;
    rightForearmAngle = +110;
    rightArmRotation = 0;

    leftForearm = new Rectangle(_r * FOREARM_LENGTH_MULTIPLIER, _r * FOREARM_WIDTH_MULTIPLIER, (GLfloat) 153 / 255,
                                (GLfloat) 204 / 255, (GLfloat) 50 / 255);
    rightForearm = new Rectangle(_r * FOREARM_LENGTH_MULTIPLIER, _r * FOREARM_WIDTH_MULTIPLIER, (GLfloat) 153 / 255,
                                 (GLfloat) 204 / 255, (GLfloat) 50 / 255);

    leftHandX = 0;
    leftHandY = _r * FOREARM_LENGTH_MULTIPLIER;

    rightHandX = 0;
    rightHandY = _r * FOREARM_LENGTH_MULTIPLIER;

    leftHand = new Circle(_r * HAND_SIZE_MULTIPLIER, (GLfloat) 131 / 255, 0, 0);
    rightHand = new Circle(_r * HAND_SIZE_MULTIPLIER, (GLfloat) 131 / 255, 0, 0);

}

void Player::draw() {
    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    drawHead();
    drawNose();

    drawLeftArm();
    drawRightArm();

//    drawBarrier();

    glPopMatrix();
}


void Player::drawHead() {
    head->draw();
}

void Player::drawNose() {
    glPushMatrix();

    glTranslatef(noseX, noseY, 0);
    nose->draw();

    glPopMatrix();
}


void Player::drawLeftArm() {
    glPushMatrix();

    glTranslatef(leftArmX, leftArmY, 0);
    glRotatef(leftArmAngle + leftArmRotation, 0, 0, 1);
    leftArm->draw();

    glTranslatef(leftForearmX, leftForearmY, 0);
    glRotatef(leftForearmAngle + leftForearmRotation, 0, 0, 1);
    leftForearm->draw();

    glTranslatef(leftHandX, leftHandY, 0);
    leftHand->draw();

    glPopMatrix();
}

void Player::drawRightArm() {
    glPushMatrix();

    glTranslatef(rightArmX, rightArmY, 0);
    glRotatef(rightArmAngle + rightArmRotation, 0, 0, 1);
    rightArm->draw();

    glTranslatef(rightForearmX, rightForearmY, 0);
    glRotatef(rightForearmAngle + rightForearmRotation, 0, 0, 1);
    rightForearm->draw();

    glTranslatef(rightHandX, rightHandY, 0);
    rightHand->draw();

    glPopMatrix();
}

void Player::drawBarrier() const {
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

void Player::walk(GLdouble deltaTime, Player &player, Arena &arena) {
    double rad = Utils::degToRad(angle);
    GLfloat xIncrement = deltaTime * LINEAR_VELOCITY * cos(rad);
    GLfloat yIncrement = deltaTime * LINEAR_VELOCITY * sin(rad);
    treatPlayerCollision(xIncrement, yIncrement, player, deltaTime > 0 ? deltaTime : -deltaTime);
    treatArenaCollision(arena, xIncrement, yIncrement);

    x += xIncrement;
    y += yIncrement;
}

//TODO: QUANDO O SOCO ESTA VOLTANDO AOS POUCOS SE O JOGADOR CLICAR PARA SOCAR NOVAMENTE O SOCO VOLTA INSTANTANEO. PARA OBSERVAR O EFEITO ABAIXE A VELOCIDADE DE VOLTA DO SOCO
//TODO: AJUSTAR LOGICA DO SOCO ATUALMENTE SEMPPRE CONSIDERA O CLICK INICIAL PARA MEDIR A DISTANCIA. TROCAR O CLICL INICIAL PELA POSICAO EM QUE O MOVIMENTO SE INVERTEU
void Player::treatPunch(GLdouble deltaTime, Mouse &mouse, Arena &arena, Player &player) {
    GLfloat rotationPercent = (mouse.movedX - mouse.clickX) / (arena.width / 2);

    if (mouse.button == 0 && mouse.state == 0 && mouse.movedX - mouse.clickX <= arena.width / 2) {
        rightArmRotation = ARM_ANGULAR_AMPLITUDE * rotationPercent >= 0 ? ARM_ANGULAR_AMPLITUDE * rotationPercent : 0;
        rightForearmRotation =
                -FOREARM_ANGULAR_AMPLITUDE * rotationPercent <= 0 ? -FOREARM_ANGULAR_AMPLITUDE * rotationPercent : 0;
    }
    if (mouse.button == 0 && mouse.state == 0 && -(mouse.movedX - mouse.clickX) <= arena.width / 2) {
        leftArmRotation = ARM_ANGULAR_AMPLITUDE * rotationPercent <= 0 ? ARM_ANGULAR_AMPLITUDE * rotationPercent : 0;
        leftForearmRotation =
                -FOREARM_ANGULAR_AMPLITUDE * rotationPercent >= 0 ? -FOREARM_ANGULAR_AMPLITUDE * rotationPercent : 0;
    }

    //TODO: OLHAR SE REALMENTE || EH O OPERADOR CORRETO -> PROVAVELMENTE EH
    if (mouse.state == 1 && (rightArmRotation > 0 || rightForearmRotation < 0)) {
        rightArmRotation = rightArmRotation - ARM_ANGULAR_VELOCITY * deltaTime >= 0 ? rightArmRotation -
                                                                                      ARM_ANGULAR_VELOCITY * deltaTime
                                                                                    : 0;
        rightForearmRotation =
                rightForearmRotation + FOREARM_ANGULAR_VELOCITY * deltaTime <= 0 ? rightForearmRotation +
                                                                                   FOREARM_ANGULAR_VELOCITY * deltaTime
                                                                                 : 0;

//        if (rightArmRotation == 0 && rightForearmRotation == 0) {
//            bypassMouse = false;
//        }
    }
    if (mouse.state == 1 && (leftArmRotation < 0 || leftForearmRotation > 0)) {
        leftArmRotation = leftArmRotation + ARM_ANGULAR_VELOCITY * deltaTime <= 0 ? leftArmRotation +
                                                                                    ARM_ANGULAR_VELOCITY * deltaTime
                                                                                  : 0;
        leftForearmRotation =
                leftForearmRotation - FOREARM_ANGULAR_VELOCITY * deltaTime >= 0 ? leftForearmRotation -
                                                                                  FOREARM_ANGULAR_VELOCITY * deltaTime
                                                                                : 0;

//        if (leftArmRotation == 0 && leftForearmRotation == 0) {
//            bypassMouse = false;
//        }
    }

    if ((getLeftHandCollision(player) || getRightHandCollision(player)) && mouse.state == 0) {
        mouse.state = 1;
        score++;
    }

}

void Player::treatArenaCollision(Arena &arena, GLfloat &xIncrement, GLfloat &yIncrement) const {
    if (x + xIncrement + getR() >= arena.x + arena.width || x + xIncrement - getR() <= arena.x) {
        xIncrement = 0;
    }
    if (y + yIncrement + getR() >= arena.y + arena.height || y + yIncrement - getR() <= arena.y) {
        yIncrement = 0;
    }
}

//TODO: COLLISION TREATMENT IS MAKING PLAYER "JUMP"
void Player::treatPlayerCollision(GLfloat &xIncrement, GLfloat &yIncrement, Player &player, GLdouble deltaTime) const {
    bool collision = Utils::distance(x + xIncrement, y + yIncrement, player.getX(), player.getY()) <=
                     getBarrier() + player.getR();

    if (collision) {

        GLfloat xNormal = getX() - player.getX();
        GLfloat yNormal = getY() - player.getY();
        double magnitude = Utils::magnitude(xNormal, yNormal);

        xNormal /= magnitude;
        yNormal /= magnitude;

        xIncrement += deltaTime * LINEAR_VELOCITY * xNormal;
        yIncrement += deltaTime * LINEAR_VELOCITY * yNormal;

//        printf("players collided. Normal magnitude: %lf x: %f y: %f\n", Utils::magnitude(xNormal, yNormal), xNormal, yNormal);
    }
}

void Player::getLeftHandPosition() {
    GLfloat handX = 0;
    GLfloat handY = 0;

    Utils::translate(handX, handY, leftHandX, leftHandY);

    Utils::rotate(handX, handY, leftForearmAngle + leftForearmRotation);
    Utils::translate(handX, handY, leftForearmX, leftForearmY);

    Utils::rotate(handX, handY, leftArmAngle + leftArmRotation);
    Utils::translate(handX, handY, leftArmX, leftArmY);

    Utils::rotate(handX, handY, angle);
    Utils::translate(handX, handY, x, y);

    leftFistX = handX;
    leftFistY = handY;
}

void Player::getRightHandPosition() {
    GLfloat handX = 0;
    GLfloat handY = 0;

    Utils::translate(handX, handY, rightHandX, rightHandY);

    Utils::rotate(handX, handY, rightForearmAngle + rightForearmRotation);
    Utils::translate(handX, handY, rightForearmX, rightForearmY);

    Utils::rotate(handX, handY, rightArmAngle + rightArmRotation);
    Utils::translate(handX, handY, rightArmX, rightArmY);

    Utils::rotate(handX, handY, angle);
    Utils::translate(handX, handY, x, y);

    rightFistX = handX;
    rightFistY = handY;
}

bool Player::getLeftHandCollision(Player &player) {
    getLeftHandPosition();
    return Utils::distance(player.x, player.y, leftFistX, leftFistY) < getHandSize() + player.getR();
}

bool Player::getRightHandCollision(Player &player) {
    getRightHandPosition();
    return Utils::distance(player.x, player.y, rightFistX, rightFistY) < getHandSize() + player.getR();
}