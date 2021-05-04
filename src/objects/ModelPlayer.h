//
// Created by otavio on 04/05/2021.
//

#ifndef T3_MODELPLAYER_H
#define T3_MODELPLAYER_H

#define LINEAR_VELOCITY 0.1
#define ANGULAR_VELOCITY 0.1

#include "../model/Model.h"

class ModelPlayer {
public:
    Model model;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat angle;
    int state;
    int walkFrame;
    int punchFrame;

    void initialize(const Model& m);

    void draw();

    bool ready();

    void walk(GLdouble deltaTime);

    void rotate(GLdouble deltaTime);

    void startPunch();
};


#endif //T3_MODELPLAYER_H
