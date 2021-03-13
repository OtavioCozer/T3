//
// Created by otavio on 12/03/2021.
//

#ifndef T2_PLAYER_H
#define T2_PLAYER_H


#include "../polygons/Circle.h"
#include "../polygons/Rectangle.h"
#include "../services/Utils.h"
#include "Arena.h"

#define ANGULAR_VELOCITY 0.2
#define LINEAR_VELOCITY 0.5
#define BARRIER_SIZE_MULTIPLIER 2.5

class Player {
private:
    GLfloat x;
    GLfloat y;
    GLfloat angle;

    Circle *head;
    Circle *nose;

    Rectangle *leftArm;
    Rectangle *leftForearm;
    Circle *leftHand;

    Rectangle *rightArm;
    Rectangle *rightForearm;
    Circle *rightHand;

public:
    GLfloat getX() const;

    GLfloat getY() const;

    GLfloat getR() const;

    GLfloat getBarrier() const;

    void initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color);

    void draw();

    void drawBarrier();

    void rotate(GLdouble deltaTime);

    void walk(GLdouble deltaTime, Player &player, Arena &arena);

    void treatArenaCollision(Arena &arena, GLfloat &xIncrement, GLfloat &yIncrement);

    void treatPlayerCollision(GLfloat &xIncrement, GLfloat &yIncrement, Player &player, GLdouble deltaTime);
};


#endif //T2_PLAYER_H
