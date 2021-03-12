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
    Arena *arena;

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

    bool checkPlayerCollision(GLfloat _x, GLfloat _y, Player &player);

public:
    GLfloat getX() const;

    GLfloat getY() const;

    GLfloat getR() const;

    void setArena(Arena *_arena);

    void initializePlayer(GLfloat _x, GLfloat _y, GLfloat _angle, GLfloat _r, const std::string &color);

    void draw();

    void drawBarrier();

    void rotate(GLdouble deltaTime);

    void walk(GLdouble deltaTime, Player &player);
};


#endif //T2_PLAYER_H
