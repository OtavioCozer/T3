//
// Created by otavio on 04/05/2021.
//

#ifndef T3_MODELPLAYER_H
#define T3_MODELPLAYER_H

#define LINEAR_VELOCITY 0.1
#define ANGULAR_VELOCITY 0.1
#define MODEL_SCALE 100.0
#define HAND_INDEX 22074
#define EYE_INDEX 996
#define FIST_INDEX 20998

#include "../model/Model.h"
#include "../objects/Arena.h"

class ModelPlayer {
public:
    Model model;
    GLfloat x{};
    GLfloat y{};
    GLfloat z{};
    GLfloat r{};
    GLfloat angle{};
    int state{};
    int score{};

    void initialize(Model &m, bool _p1, GLfloat a, GLfloat _x, GLfloat _y, GLfloat _z);

    void draw();

    bool ready();

    void walk(GLdouble deltaTime, ModelPlayer &player, Arena arena);

    void rotate(GLdouble deltaTime, ModelPlayer &player, Arena arena);

    void startPunch();

    POS getLightPos() const;

    POS getLightTarget() const;

    POS getPerspTarget() const;

    POS getFistPos();

    POS getFistTarget();

    POS getFistUp();

    POS getEyePos();

    POS getEyeTarget();

    POS getHandPos();

    void checkPunch(ModelPlayer &player);

    void updateFrame();

private:
    int walkFrame{};
    int punchFrame{};
    bool punchConfirm{};
    bool p1{};
};


#endif //T3_MODELPLAYER_H
