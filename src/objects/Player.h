//
// Created by otavio on 12/03/2021.
//

#ifndef T2_PLAYER_H
#define T2_PLAYER_H


#include "../polygons/Circle.h"
#include "../polygons/Rectangle.h"
#include "../services/Utils.h"
#include "Arena.h"
#include "../input/Mouse.h"

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

#define ARM_ANGULAR_VELOCITY 1
#define FOREARM_ANGULAR_VELOCITY 1

class Player {
private:
    Circle *head;
    GLfloat x;
    GLfloat y;
    GLfloat angle;

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


    void treatArenaCollision(Arena &arena, GLfloat &xIncrement, GLfloat &yIncrement);

    void treatPlayerCollision(GLfloat &xIncrement, GLfloat &yIncrement, Player &player, GLdouble deltaTime);

public:
    GLfloat getX() const;

    GLfloat getY() const;

    GLfloat getR() const;

    GLfloat getBarrier() const;

    void initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color);

    void draw();

    void drawHead();

    void drawNose();

    void drawLeftArm();

    void drawRightArm();

    void drawBarrier() const;

    void rotate(GLdouble deltaTime);

    void walk(GLdouble deltaTime, Player &player, Arena &arena);

    void treatPunch(GLdouble deltaTime, Mouse &mouse, Arena &arena);
};


#endif //T2_PLAYER_H
