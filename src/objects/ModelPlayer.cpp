//
// Created by otavio on 04/05/2021.
//

#include "ModelPlayer.h"
#include "../services/Utils.h"

void ModelPlayer::initialize(const Model &m) {
    model = m;
    x = y = z = punchFrame = walkFrame = angle = state = 0;
}


void ModelPlayer::draw() {
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(angle, 0, 1, 0);

    if (state == 0) {
        model.draw(model.idle);
        walkFrame = 0;
        punchFrame = 0;
    } else if (state == 1) {
        model.draw(model.fwalk[walkFrame]);
        walkFrame++;
        walkFrame = walkFrame % 24;
    } else if (state == 2) {
        model.draw(model.bwalk[walkFrame]);
        walkFrame++;
        walkFrame = walkFrame % 24;
    } else if (state == 3) {
        model.draw(model.punch[punchFrame]);
        punchFrame++;
        punchFrame = punchFrame % 42;

    }

    glPopMatrix();
}

bool ModelPlayer::ready() {
    if (punchFrame == 0) {
        state = 0;
        return true;
    }

    return false;
}


void ModelPlayer::walk(GLdouble deltaTime) {
    double rad = Utils::degToRad(angle);
    GLfloat zIncrement = deltaTime * LINEAR_VELOCITY * cos(rad);
    GLfloat xIncrement = deltaTime * LINEAR_VELOCITY * sin(rad);

    x += xIncrement;
    z += zIncrement;
    if (deltaTime > 0) {
        state = 1;
    } else {
        state = 2;
    }
}

void ModelPlayer::rotate(GLdouble deltaTime) {
    walk(deltaTime > 0 ? deltaTime * 0.1 : -deltaTime * 0.1);
    angle += deltaTime * ANGULAR_VELOCITY;
}

void ModelPlayer::startPunch() {
    state = 3;
}



