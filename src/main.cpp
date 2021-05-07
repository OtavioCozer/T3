#include <cmath>
#include <iostream>
#include <cstdlib>
#include "tinyxml/tinystr.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <GL/glut.h>
#include "tinyxml/tinyxml.h"
#include "objects/Arena.h"
#include "input/Mouse.h"
#include "model/Model.h"
#include "objects/ModelPlayer.h"
#include "objects/Camera.h"
#include "services/Utils.h"

#include <unistd.h>

int keyStatus[256];

Arena arena;
Mouse mouse;

Camera camera;
ModelPlayer mp1, mp2;
Model m;

bool gameOver = false;
bool nightMode = false;
bool textureEnabled = true;
static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;

void readXml(char *const fileName) {
    TiXmlDocument doc(fileName);
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("reading xml: %s\n", fileName);
    } else {
        printf("Failed to load file \"%s\"\n", fileName);
        exit(0);
    }

    TiXmlNode *pParent = doc.FirstChild();
    std::string p1Color = "green";
    GLfloat cy1;

    for (TiXmlNode *pChild = pParent->FirstChild(); pChild != nullptr; pChild = pChild->NextSibling()) {

        TiXmlElement *element = pChild->ToElement();
        std::string tag = element->Value();

        if (tag == "rect") {
            arena.initialize(
                    std::stof(element->Attribute("x")),
                    0,
                    std::stof(element->Attribute("y")),
                    std::stof(element->Attribute("height")),
                    std::stof(element->Attribute("width"))
            );
        } else if (tag == "circle" && p1Color == element->Attribute("fill")) {
            cy1 = arena.z + (arena.z + arena.height) - std::stof(element->Attribute("cy")) * ARENA_SCALE;
            mp1.initialize(m, true, 0, std::stof(element->Attribute("cx")) * ARENA_SCALE, 0, cy1);
        } else if (tag == "circle") {
            cy1 = arena.z + (arena.z + arena.height) - std::stof(element->Attribute("cy")) * ARENA_SCALE;
            mp2.initialize(m, false, 0, std::stof(element->Attribute("cx")) * ARENA_SCALE, 0, cy1);
        }
    }

    double deg = Utils::radToDeg(std::atan2(mp1.x - mp2.x, mp1.z - mp2.z));
    mp1.angle = deg + 180;
    mp2.angle = deg;
}

void drawChars(GLfloat x, GLfloat y, GLfloat z, const char *text, double r, double g, double b) {
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //Draw text in the x, y, z position
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    const char *tmpStr;
    tmpStr = text;
    while (*tmpStr) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}

void drawMap(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b) {
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    GLfloat x1 = (mp1.x - arena.x) / arena.width;
    GLfloat y1 = (mp1.z - arena.z) / arena.height;
    GLfloat x2 = (mp2.x - arena.x) / arena.width;
    GLfloat y2 = (mp2.z - arena.z) / arena.height;

    x1 = (x1 / 4) + x;
    y1 = (y1 / 4) + y;
    x2 = (x2 / 4) + x;
    y2 = (y2 / 4) + y;

    GLfloat size = 0.249;

    glColor3f(r, g, b);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, z);
    glVertex3f(x + size, y, z);
    glVertex3f(x + size, y + size, z);
    glVertex3f(x, y + size, z);
    glEnd();

    int num_segments = 15;
    float rc = 0.02;

    float theta;
    float xc;
    float yc;

    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        xc = rc * cosf(theta);//calculate the x component
        yc = rc * sinf(theta);//calculate the y component

        glVertex2f(xc + x1, yc + y1);//output vertex

    }
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        xc = rc * cosf(theta);//calculate the x component
        yc = rc * sinf(theta);//calculate the y component

        glVertex2f(xc + x2, yc + y2);//output vertex

    }
    glEnd();

    glPopAttrib();
}

void drawHud() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);

    sprintf(str, "Jogador: %d Computador: %d", mp1.score, mp2.score);
    drawChars(0.3, 0.95, 0, str, 1, 0, 0);

    if (camera.state == 0) {
        sprintf(str, "Camera 0");
    } else if (camera.state == 1) {
        sprintf(str, "Camera 1");
    } else if (camera.state == 2) {
        sprintf(str, "Camera 2");
    } else if (camera.state == 3) {
        sprintf(str, "Camera 3");
    }
    drawChars(0.1, 0.95, 0, str, 1, 0, 0);

    drawMap(0.749, 0.01, 0, 0, 0, 1);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void showGameOver(GLfloat x, GLfloat y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);

    if (mp1.score >= 10) {
        drawChars(x, y, 0, "VOCE GANHOU", 1, 0, 0);
    } else {
        drawChars(x, y, 0, "VOCE PERDEU", 1, 0, 0);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void changeCamera(int state) {
    if (state == 0) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (GLfloat) 500 / (GLfloat) 500, 1, 10000);

        camera.initialize(600, 600, 600, -600, -600, -600, 0, 1, 0, 0);
    } else if (state == 1) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (GLfloat) 500 / (GLfloat) 500, 15, 10000);

        pos eye = mp1.getEyePos();
        pos target = mp1.getEyeTarget();
        camera.initialize(eye.x, eye.y, eye.z, target.x, target.y, target.z, 0, 1, 0, 1);
    } else if (state == 2) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (GLfloat) 500 / (GLfloat) 500, 3, 10000);

        pos eye = mp1.getFistPos();
        pos target = mp1.getFistTarget();
        pos up = mp1.getFistUp();
        camera.initialize(eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z, 2);
    } else if (state == 3) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (GLfloat) 500 / (GLfloat) 500, 1, 10000);

        pos target = mp1.getPerspTarget();
        camera.state = 3;

        camera.centerX = target.x;
        camera.centerY = target.y;
        camera.centerZ = target.z;

        camera.eyeX = camera.r * cos(Utils::degToRad(camera.XYAngle)) * cos(Utils::degToRad(camera.XZAngle));
        camera.eyeY = camera.r * -sin(Utils::degToRad(camera.XZAngle));
        camera.eyeZ = camera.r * sin(Utils::degToRad(camera.XYAngle)) * cos(Utils::degToRad(camera.XZAngle));
    }
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'y':
            mp1.increasePropertieNumber();
            break;
        case 'h':
            mp1.decreasePropertieNumber();
            break;
        case 'u':
            mp1.increasePropertie();
            break;
        case 'j':
            mp1.decreasePropertie();
            break;
        case 'i':
            mp1.changeValue(+5);
            break;
        case 'k':
            mp1.changeValue(-5);
            break;
        case 'r':
            mp1.restartMaterial();
            break;
        case 'a':
        case 'A':
            keyStatus[(int) ('a')] = 1;
            break;
        case 'd':
        case 'D':
            keyStatus[(int) ('d')] = 1;
            break;
        case 'w':
        case 'W':
            keyStatus[(int) ('w')] = 1;
            break;
        case 's':
        case 'S':
            keyStatus[(int) ('s')] = 1;
            break;
        case 'q':
        case 'Q':
            keyStatus[(int) ('q')] = 1;
            break;
        case 't':
            textureEnabled = !textureEnabled;
            if (textureEnabled) {
                glEnable(GL_TEXTURE_2D);
            } else {
                glDisable(GL_TEXTURE_2D);
            };
            break;
        case '7':
            camera.eyeX += 10;
            break;
        case '4':
            camera.eyeX -= 10;
            break;
        case '8':
            camera.eyeY += 10;
            break;
        case '5':
            camera.eyeY -= 10;
            break;
        case '9':
            camera.eyeZ += 10;
            break;
        case '6':
            camera.eyeZ -= 10;
            break;
        case '0':
            changeCamera(0);
            break;
        case '1':
            changeCamera(1);
            break;
        case '2':
            changeCamera(2);
            break;
        case '3':
            camera.r = 3 * 100;
            changeCamera(3);
            break;
        case '+':
            camera.r += 10;
            break;
        case '-':
            camera.r -= 10;
            break;
        case 'n':
        case 'N':
            nightMode = !nightMode;
            break;
        case 27:
            exit(0);
        case ' ':
            mp1.printMaterial();
            keyStatus[(int) (' ')] = !keyStatus[(int) (' ')];
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y) {
    if (key != ' ') {
        keyStatus[(int) (key)] = 0;
    }
    glutPostRedisplay();
}

void ResetKeyStatus() {
    for (int i = 0; i < 256; i++) {
        keyStatus[i] = 0;
    }
}

void motion(int x, int y) {
    if (!mouse.state || (camera.state != 0 && camera.state != 3)) {
        return;
    }

    camera.XZAngle += x - mouse.lastX;
    camera.XZAngle = (int) camera.XZAngle % 360;

    if (camera.XYAngle + y - mouse.lastY > -60 && camera.XYAngle + y - mouse.lastY < 60) {
        camera.XYAngle += y - mouse.lastY;
    }

    mouse.lastX = x;
    mouse.lastY = y;

    camera.centerX = cos(Utils::degToRad(camera.XYAngle)) * cos(Utils::degToRad(camera.XZAngle));
    camera.centerY = -sin(Utils::degToRad(camera.XZAngle));
    camera.centerZ = sin(Utils::degToRad(camera.XYAngle)) * cos(Utils::degToRad(camera.XZAngle));
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        mouse.lastX = x;
        mouse.lastY = y;
        mouse.state = 1;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouse.state = 0;
    }
}

void init(char *const fileName) {
    arena.initializeTexture();
    m.initialize();

    readXml(fileName);
    mouse.state = 0;
    ResetKeyStatus();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glDepthFunc(GL_LEQUAL);
    changeCamera(1);
}

void drawAxes(double size, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat color_r[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat color_g[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat color_b[] = {0.0, 0.0, 1.0, 1.0};

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //x axis
    glPushMatrix();
    glColor3fv(color_r);
    glScalef(size, size * 0.1, size * 0.1);
    glTranslatef(0.5, 0, 0);  // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    //y axis
    glPushMatrix();
    glColor3fv(color_g);
    glRotatef(90, 0, 0, 1);
    glScalef(size, size * 0.1, size * 0.1);
    glTranslatef(0.5, 0, 0);  // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    //z axis
    glPushMatrix();
    glColor3fv(color_b);
    glRotatef(-90, 0, 1, 0);
    glScalef(size, size * 0.1, size * 0.1);
    glTranslatef(0.5, 0, 0);  // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    glPopAttrib();
}

void defineLight() {
    if (nightMode) {
        GLfloat ambient[] = {0, 0, 0, 1};
        GLfloat diffuse[] = {1, 1, 1, 1};
        GLfloat specular[] = {1, 1, 1, 1};
        GLfloat cutoff[] = {35};

        // ============= LIGHT 0
        pos pos1 = mp1.getLightPos();
        GLfloat light0_position[] = {pos1.x, pos1.y, pos1.z, 1};
        pos target1 = mp1.getLightTarget();
        GLfloat light0_target[] = {target1.x - pos1.x, target1.y - pos1.y, target1.z - pos1.z};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_target);
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

        glDisable(GL_LIGHTING);
        glPointSize(15);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        glVertex3f(light0_position[0], light0_position[1], light0_position[2]);
        glVertex3f(light0_target[0], light0_target[1], light0_target[2]);
        glEnd();
        glEnable(GL_LIGHTING);

        // ============= LIGHT 1
        pos pos2 = mp2.getLightPos();
        GLfloat light1_position[] = {pos2.x, pos2.y, pos2.z, 1};
        pos target2 = mp2.getLightTarget();
        GLfloat light1_target[] = {target2.x - pos2.x, target2.y - pos2.y, target2.z - pos2.z};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_target);
        glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

        glDisable(GL_LIGHTING);
        glPointSize(15);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        glVertex3f(light1_position[0], light1_position[1], light1_position[2]);
        glVertex3f(light1_target[0], light1_target[1], light1_target[2]);
        glEnd();
        glEnable(GL_LIGHTING);


    } else {
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);
        GLfloat light_position[] = {arena.x + (arena.width / 2), 2 * 120, arena.z + (arena.height / 2), 1};
        GLfloat cutoff[] = {180};
        GLfloat ambient[] = {0, 0, 0, 1};
        GLfloat diffuse[] = {1, 1, 1, 1};
        GLfloat specular[] = {1, 1, 1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

        glDisable(GL_LIGHTING);
        glPointSize(15);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        glVertex3f(light_position[0], light_position[1], light_position[2]);
        glEnd();
        glEnable(GL_LIGHTING);
    }
}

void enemieDisplay() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat) 500 / (GLfloat) 250, 15, 10000);

    glViewport(0, 500, 500, 250);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    pos eye = mp2.getEyePos();
    pos target = mp2.getEyeTarget();

    gluLookAt(eye.x, eye.y, eye.z, target.x, target.y, target.z, 0, 1, 0);

    defineLight();

    if (!gameOver) {
        mp1.draw();
        mp2.draw();
        arena.draw();
    }
}

void myDisplay() {
    changeCamera(camera.state);
    glViewport(0, 0, 500, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (camera.state == 0) {
        gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.eyeX + camera.centerX, camera.eyeY + camera.centerY,
                  camera.eyeZ + camera.centerZ, camera.upX, camera.upY, camera.upZ);
    } else if (camera.state == 1) {
        pos eye = mp1.getEyePos();
        pos target = mp1.getEyeTarget();
        camera.initialize(eye.x, eye.y, eye.z, target.x, target.y, target.z, 0, 1, 0, 1);

        gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.centerX, camera.centerY, camera.centerZ, camera.upX,
                  camera.upY, camera.upZ);
    } else if (camera.state == 2) {
        pos eye = mp1.getFistPos();
        pos target = mp1.getFistTarget();
        pos up = mp1.getFistUp();
        camera.initialize(eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z, 2);

        gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.centerX, camera.centerY, camera.centerZ, camera.upX,
                  camera.upY, camera.upZ);
    } else if (camera.state == 3) {
        pos target = mp1.getPerspTarget();
        camera.state = 3;

        camera.centerX = target.x;
        camera.centerY = target.y;
        camera.centerZ = target.z;

        camera.eyeX = camera.r * cos(Utils::degToRad(camera.XZAngle)) * cos(Utils::degToRad(camera.XYAngle)) + target.x;
        camera.eyeY = camera.r * -sin(Utils::degToRad(camera.XYAngle)) + target.y;
        camera.eyeZ = camera.r * sin(Utils::degToRad(camera.XZAngle)) * cos(Utils::degToRad(camera.XYAngle)) + target.z;

        gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.centerX, camera.centerY, camera.centerZ, camera.upX,
                  camera.upY, camera.upZ);
    }

    defineLight();

    drawAxes(50, 0, 0, 0);

    gameOver = mp1.score >= 10 || mp2.score >= 10;

    if (!gameOver) {
        drawHud();
        mp1.draw();
        mp2.draw();
        arena.draw();
    } else {
        showGameOver(0.45, 0.5);
    }
}

void display() {
    glClearColor(102.0 / 255.0, 153.0 / 255.0, 153.0 / 255.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    myDisplay();
    enemieDisplay();

    glutSwapBuffers();
}

void idle() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDifference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;

    static GLdouble previousTimePunch = glutGet(GLUT_ELAPSED_TIME);
    GLdouble timeDifferencePunch = currentTime - previousTimePunch;


    if (keyStatus[(int) (' ')]) {
        if (mp2.ready()) {
            if (timeDifferencePunch > 2500) {
                mp2.startPunch();
                previousTimePunch = currentTime;
            } else {
                mp2.walk(0.1 * timeDifference, mp1, arena);
                mp2.angle = Utils::radToDeg(std::atan2(mp1.x - mp2.x, mp1.z - mp2.z));

            }
        } else {
            mp2.checkPunch(mp1);
        }
    }

    if (mp1.ready()) {
        if (keyStatus[(int) ('w')]) {
            mp1.walk(timeDifference, mp2, arena);
        }
        if (keyStatus[(int) ('s')]) {
            mp1.walk(-timeDifference, mp2, arena);
        }
        if (keyStatus[(int) ('a')]) {
            mp1.rotate(timeDifference, mp2, arena);
        }
        if (keyStatus[(int) ('d')]) {
            mp1.rotate(-timeDifference, mp2, arena);
        }
        if (keyStatus[(int) ('q')]) {
            mp1.startPunch();
        }
    } else {
        mp1.checkPunch(mp2);
    }

    mp1.updateFrame();
    mp2.updateFrame();
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Create window
    glutInitWindowSize(500, 750);
    glutInitWindowPosition(1200, 300);
    glutCreateWindow("T3");

    init(argv[1]);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);

    glutMotionFunc(motion);
    glutMouseFunc(mouseFunc);

    glutMainLoop();

    return 0;
}