//
// Created by otavio on 04/05/2021.
//

#include "ModelPlayer.h"

#include "../services/Utils.h"

void ModelPlayer::initialize(Model &m, bool _p1, GLfloat a, GLfloat _x, GLfloat _y, GLfloat _z) {
    model = m;
    x = _x;
    y = _y;
    z = _z;
    r = 0.366 * MODEL_SCALE;
    angle = a;
    punchFrame = walkFrame = state = 0;
    punchConfirm = false;
    score = 0;
    p1 = _p1;

    if (p1) {
        model.material.materialAmbient[1] = 0.2;
        model.material.materialDiffuse[1] = 30;
        model.material.materialSpecular[1] = 30;
        model.material.materialEmission[1] = 0.3;
    } else {
        model.material.materialAmbient[0] = 0.2;
        model.material.materialDiffuse[0] = 30;
        model.material.materialSpecular[0] = 30;
        model.material.materialEmission[0] = 0.3;
    }
}

void ModelPlayer::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 0, 1, 0);
    glScalef(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);

    if (state == 0) {
        model.draw(model.idle);
    } else if (state == 1) {
        model.draw(model.fwalk[walkFrame]);
    } else if (state == 2) {
        model.draw(model.bwalk[walkFrame]);
    } else if (state == 3) {
        model.draw(model.punch[punchFrame]);
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


void ModelPlayer::walk(GLdouble deltaTime, ModelPlayer &player, Arena arena) {
    double rad = Utils::degToRad(angle);
    GLfloat p2x = player.x;
    GLfloat p2z = player.z;
    GLfloat xIncrement = deltaTime * LINEAR_VELOCITY * sin(rad);
    GLfloat zIncrement = deltaTime * LINEAR_VELOCITY * cos(rad);

    if (Utils::distance(x, z + zIncrement, p2x, p2z) > 2 * r && z + zIncrement + r < arena.z + arena.height &&
        z + zIncrement > arena.z + r) {
        z += zIncrement;
    }
    if (Utils::distance(x + xIncrement, z, p2x, p2z) > 2 * r && x + xIncrement + r < arena.x + arena.width &&
        x + xIncrement > arena.x + r) {
        x += xIncrement;
    }

    if (deltaTime > 0) {
        state = 1;
    } else {
        state = 2;
    }
}

void ModelPlayer::rotate(GLdouble deltaTime, ModelPlayer &player, Arena arena) {
    walk(deltaTime > 0 ? deltaTime * 0.1 : -deltaTime * 0.1, player, arena);
    angle += deltaTime * ANGULAR_VELOCITY;
}

void ModelPlayer::startPunch() {
    punchConfirm = false;
    state = 3;
}

POS ModelPlayer::getLightPos() {
    GLfloat xTarget = 0;
    GLfloat yTarget = 2.8;
    GLfloat zTarget = 0;

    Utils::scale(xTarget, yTarget, zTarget, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xTarget, yTarget, zTarget, 0, 1, 0, angle);
    Utils::translate3(xTarget, yTarget, zTarget, x, y, z);

    pos target = {xTarget, yTarget, zTarget};
    return target;
}

POS ModelPlayer::getLightTarget() {
    GLfloat xTarget = 0;
    GLfloat yTarget = 0;
    GLfloat zTarget = 0;

    Utils::scale(xTarget, yTarget, zTarget, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xTarget, yTarget, zTarget, 0, 1, 0, angle);
    Utils::translate3(xTarget, yTarget, zTarget, x, y, z);

    pos target = {xTarget, yTarget, zTarget};
    return target;
}

POS ModelPlayer::getPerspPos() {
    GLfloat xPersp = 0;
    GLfloat yPersp = 1.8;
    GLfloat zPersp = -1.5;

    Utils::scale(xPersp, yPersp, zPersp, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xPersp, yPersp, zPersp, 0, 1, 0, angle);
    Utils::translate3(xPersp, yPersp, zPersp, x, y, z);

    pos persp = {xPersp, yPersp, zPersp};
    return persp;
}

POS ModelPlayer::getPerspTarget() const {
    GLfloat xTarget = 0;
    GLfloat yTarget = 1;
    GLfloat zTarget = 0;

    Utils::scale(xTarget, yTarget, zTarget, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xTarget, yTarget, zTarget, 0, 1, 0, angle);
    Utils::translate3(xTarget, yTarget, zTarget, x, y, z);

    pos target = {xTarget, yTarget, zTarget};
    return target;
}

POS ModelPlayer::getPerspUp() {
    GLfloat xUp = model.punch[punchFrame].vertsNorm[FIST_INDEX].x;
    GLfloat yUp = model.punch[punchFrame].vertsNorm[FIST_INDEX].y;
    GLfloat zUp = model.punch[punchFrame].vertsNorm[FIST_INDEX].z;

    Utils::scale(xUp, yUp, zUp, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xUp, yUp, zUp, 0, 1, 0, angle);
    Utils::translate3(xUp, yUp, zUp, x, y, z);

    pos up = {0, 1, 0};
    return up;
}

POS ModelPlayer::getFistPos() {
    GLfloat xFist = model.punch[punchFrame].vertsPos[FIST_INDEX].x;
    GLfloat yFist = model.punch[punchFrame].vertsPos[FIST_INDEX].y;
    GLfloat zFist = model.punch[punchFrame].vertsPos[FIST_INDEX].z;

    Utils::scale(xFist, yFist, zFist, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xFist, yFist, zFist, 0, 1, 0, angle);
    Utils::translate3(xFist, yFist, zFist, x, y, z);

    pos fist = {xFist, yFist, zFist};
    return fist;
}

POS ModelPlayer::getFistTarget() {
    GLfloat xTarget = model.punch[punchFrame].vertsPos[FIST_INDEX].x;
    GLfloat yTarget = model.punch[punchFrame].vertsPos[FIST_INDEX].y;
    GLfloat zTarget = model.punch[punchFrame].vertsPos[FIST_INDEX].z + 0.2;

    Utils::scale(xTarget, yTarget, zTarget, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xTarget, yTarget, zTarget, 0, 1, 0, angle);
    Utils::translate3(xTarget, yTarget, zTarget, x, y, z);

    pos target = {xTarget, yTarget, zTarget};
    return target;
}


POS ModelPlayer::getFistUp() {
    GLfloat xUp = model.punch[punchFrame].vertsNorm[FIST_INDEX].x;
    GLfloat yUp = model.punch[punchFrame].vertsNorm[FIST_INDEX].y;
    GLfloat zUp = model.punch[punchFrame].vertsNorm[FIST_INDEX].z;

    Utils::scale(xUp, yUp, zUp, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xUp, yUp, zUp, 0, 1, 0, angle);
    Utils::translate3(xUp, yUp, zUp, x, y, z);

    pos up = {0, 1, 0};
    return up;
}


POS ModelPlayer::getEyePos() {
    GLfloat xEye = model.idle.vertsPos[EYE_INDEX].x;
    GLfloat yEye = model.idle.vertsPos[EYE_INDEX].y;
    GLfloat zEye = model.idle.vertsPos[EYE_INDEX].z;

    Utils::scale(xEye, yEye, zEye, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xEye, yEye, zEye, 0, 1, 0, angle);
    Utils::translate3(xEye, yEye, zEye, x, y, z);

    pos eye = {xEye, yEye, zEye};
    return eye;
}

POS ModelPlayer::getEyeTarget() {
    GLfloat xTarget = model.idle.vertsPos[EYE_INDEX].x;
    GLfloat yTarget = model.idle.vertsPos[EYE_INDEX].y;
    GLfloat zTarget = model.idle.vertsPos[EYE_INDEX].z + 0.2;

    Utils::scale(xTarget, yTarget, zTarget, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xTarget, yTarget, zTarget, 0, 1, 0, angle);
    Utils::translate3(xTarget, yTarget, zTarget, x, y, z);

    pos target = {xTarget, yTarget, zTarget};
    return target;
}

POS ModelPlayer::getHandPos() {
    GLfloat xHand = model.punch[punchFrame].vertsPos[HAND_INDEX].x;
    GLfloat yHand = model.punch[punchFrame].vertsPos[HAND_INDEX].y;
    GLfloat zHand = model.punch[punchFrame].vertsPos[HAND_INDEX].z;

    Utils::scale(xHand, yHand, zHand, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    Utils::rotate3(xHand, yHand, zHand, 0, 1, 0, angle);
    Utils::translate3(xHand, yHand, zHand, x, y, z);

    pos hand = {xHand, yHand, zHand};
    return hand;
}

void ModelPlayer::checkPunch(ModelPlayer &player) {
    pos hand = getHandPos();
    if (Utils::distance(hand.x, hand.z, player.x, player.z) < r) {
        if (!punchConfirm) {
            punchConfirm = true;
            score++;
        }
        if (Utils::distance(x, z, player.x, player.z) < Utils::distance(x, z, hand.x, hand.z)) {
            player.x = hand.x;
            player.z = hand.z;
        }
    }
}

void ModelPlayer::updateFrame() {
    if (state == 0) {
        walkFrame = 0;
        punchFrame = 0;
    } else if (state == 1) {
        walkFrame++;
        walkFrame = walkFrame % 24;
    } else if (state == 2) {
        walkFrame++;
        walkFrame = walkFrame % 24;
    } else if (state == 3) {
        punchFrame++;
        punchFrame = punchFrame % 43;
    }
}
