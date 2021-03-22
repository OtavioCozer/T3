//
// Created by otavio on 12/03/2021.
//

#ifndef T2_PLAYER_H
#define T2_PLAYER_H


#include <stack>
#include "../polygons/Circle.h"
#include "../polygons/Rectangle.h"
#include "../services/Utils.h"
#include "../input/Mouse.h"
#include "Arena.h"

#define ANGULAR_VELOCITY 0.2
#define LINEAR_VELOCITY 0.5

#define BARRIER_SIZE_MULTIPLIER 2.5

#define NOSE_SIZE_MULTIPLIER 0.2
#define NOSE_DISTANCE_MULTIPLIER 1.01

#define ARM_LENGTH_MULTIPLIER 2.2
#define ARM_WIDTH_MULTIPLIER 0.25

#define FOREARM_LENGTH_MULTIPLIER 2
#define FOREARM_WIDTH_MULTIPLIER 0.25

#define HAND_SIZE_MULTIPLIER 0.4

#define ARM_ANGULAR_AMPLITUDE 130
#define FOREARM_ANGULAR_AMPLITUDE 45

#define ARM_ANGULAR_VELOCITY 0.8
#define FOREARM_ANGULAR_VELOCITY 0.8

class Player {
private:
    Circle *head;
    GLfloat x;
    GLfloat y;
    GLfloat angle;

    bool bypassMouse;
    int score;

    GLfloat leftFistX;
    GLfloat leftFistY;
    GLfloat rightFistX;
    GLfloat rightFistY;

    Circle *nose;
    GLfloat noseX;
    GLfloat noseY;

    Rectangle *leftArm;
    GLfloat leftArmX;
    GLfloat leftArmY;
    GLfloat leftArmAngle;
    GLfloat leftArmRotation;

    Rectangle *leftForearm;
    GLfloat leftForearmX;
    GLfloat leftForearmY;
    GLfloat leftForearmAngle;
    GLfloat leftForearmRotation;

    Circle *leftHand;
    GLfloat leftHandX;
    GLfloat leftHandY;

    Rectangle *rightArm;
    GLfloat rightArmX;
    GLfloat rightArmY;
    GLfloat rightArmAngle;
    GLfloat rightArmRotation;

    Rectangle *rightForearm;
    GLfloat rightForearmX;
    GLfloat rightForearmY;
    GLfloat rightForearmAngle;
    GLfloat rightForearmRotation;

    Circle *rightHand;
    GLfloat rightHandX;
    GLfloat rightHandY;


    void treatArenaCollision(Arena &arena, GLfloat &xIncrement, GLfloat &yIncrement) const;

    void treatPlayerCollision(GLfloat &xIncrement, GLfloat &yIncrement, Player &player, GLdouble deltaTime) const;

    void getLeftHandPosition();

    void getRightHandPosition();

    bool getLeftHandCollision(Player &player);

    bool getRightHandCollision(Player &player);

public:
    GLfloat getX() const;

    GLfloat getY() const;

    GLfloat getHandSize() const;

    GLfloat getR() const;

    GLfloat getBarrier() const;

    void setAngle(GLfloat _angle);

    int getScore() const;

    void initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color);

    void draw();

    void drawHead();

    void drawNose();

    void drawLeftArm();

    void drawRightArm();

    void drawBarrier() const;

    void rotate(GLdouble deltaTime);

    void walk(GLdouble deltaTime, Player &player, Arena &arena);

    void treatPunch(GLdouble deltaTime, Mouse &mouse, Arena &arena, Player &player);
};


#endif //T2_PLAYER_H
