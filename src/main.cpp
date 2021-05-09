#include <cmath>
#include <cstdlib>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "tinyxml/tinyxml.h"
#include "input/Mouse.h"
#include "model/Model.h"
#include "services/Utils.h"
#include "objects/Arena.h"
#include "objects/Camera.h"
#include "objects/ModelPlayer.h"

#define WIDTH 500
#define HEIGHT_MAIN 500
#define HEIGHT_ENEMY 250

//#define WIDTH 600
//#define HEIGHT_MAIN 600
//#define HEIGHT_ENEMY 300

int keyStatus[256];

Arena arena;
Mouse mouse;

Camera camera;
ModelPlayer mp1, mp2;
Model m;

bool gameOver = false;
bool nightMode = false;
bool textureEnabled = true;
bool drawLights = false;
bool axes = false;
static char str[1000];

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
            cy1 = arena.z + (arena.z + arena.height) - std::stof(element->Attribute("cy"));
            mp1.initialize(m, true, 0, std::stof(element->Attribute("cx")), 0, cy1);
        } else if (tag == "circle") {
            cy1 = arena.z + (arena.z + arena.height) - std::stof(element->Attribute("cy"));
            mp2.initialize(m, false, 0, std::stof(element->Attribute("cx")), 0, cy1);
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

    GLfloat x1 = ((mp1.x - arena.x) / arena.width) * WIDTH;
    GLfloat y1 = ((mp1.z - arena.z) / arena.height) * HEIGHT_MAIN;
    GLfloat x2 = ((mp2.x - arena.x) / arena.width) * WIDTH;;
    GLfloat y2 = ((mp2.z - arena.z) / arena.height) * HEIGHT_MAIN;

    x1 = (x1 / 4) + x;
    y1 = (y1 / 4) + y;
    x2 = (x2 / 4) + x;
    y2 = (y2 / 4) + y;

    GLfloat sizex = 0.249 * WIDTH;
    GLfloat sizey = 0.249 * HEIGHT_MAIN;

    glColor3f(r, g, b);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, z);
    glVertex3f(x + sizex, y, z);
    glVertex3f(x + sizex, y + sizey, z);
    glVertex3f(x, y + sizey, z);
    glEnd();

    int num_segments = 15;
    float rc = 0.02 * WIDTH;

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
    glOrtho(0, WIDTH, 0, HEIGHT_MAIN, -1, 1);

    sprintf(str, "Jogador: %d Computador: %d", mp1.score, mp2.score);
    drawChars(0.3 * WIDTH, 0.95 * HEIGHT_MAIN, 0, str, 1, 0, 0);

    if (camera.state == 1) {
        sprintf(str, "Camera 1");
    } else if (camera.state == 2) {
        sprintf(str, "Camera 2");
    } else if (camera.state == 3) {
        sprintf(str, "Camera 3");
    }
    drawChars(0.1 * WIDTH, 0.95 * HEIGHT_MAIN, 0, str, 1, 0, 0);

    drawMap(0.749 * WIDTH, 0.01 * HEIGHT_MAIN, 0, 0, 0, 1);

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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (state == 1) {
        gluPerspective(45, (GLfloat) WIDTH / (GLfloat) HEIGHT_MAIN, 15, 10000);

        pos eye = mp1.getEyePos();
        pos target = mp1.getEyeTarget();
        camera.initialize(eye.x, eye.y, eye.z, target.x, target.y, target.z, 0, 1, 0, 1);
    } else if (state == 2) {
        gluPerspective(45, (GLfloat) WIDTH / (GLfloat) HEIGHT_MAIN, 3, 10000);

        pos eye = mp1.getFistPos();
        pos target = mp1.getFistTarget();
        pos up = mp1.getFistUp();
        camera.initialize(eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z, 2);
    } else if (state == 3) {
        gluPerspective(45, (GLfloat) WIDTH / (GLfloat) HEIGHT_MAIN, 1, 10000);

        pos target = mp1.getPerspTarget();
        camera.state = 3;

        camera.centerX = target.x;
        camera.centerY = target.y;
        camera.centerZ = target.z;

        camera.eyeX = camera.r * cos(Utils::degToRad(camera.XYAngle)) * cos(Utils::degToRad(camera.XZAngle));
        camera.eyeY = camera.r * sin(Utils::degToRad(camera.XZAngle));
        camera.eyeZ = camera.r * sin(Utils::degToRad(camera.XYAngle)) * cos(Utils::degToRad(camera.XZAngle));
    }
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
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
            }
            break;
        case 'l':
            drawLights = !drawLights;
            break;
        case 'm':
            arena.dWall = !arena.dWall;
            break;
        case 'e':
            axes = !axes;
            break;
        case 'n':
        case 'N':
            nightMode = !nightMode;
            break;
        case '1':
            changeCamera(1);
            break;
        case '2':
            changeCamera(2);
            break;
        case '3':
            camera.r = 3 * MODEL_SCALE;
            camera.XYAngle = +20;
            camera.XZAngle = 270 - mp1.angle;
            changeCamera(3);
            break;
        case '+':
            camera.r += 10;
            break;
        case '-':
            camera.r -= 10;
            break;
        case 27:
            exit(0);
        case ' ':
            keyStatus[(int) (' ')] = !keyStatus[(int) (' ')];
            mp2.state = 0;
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

void resetKeyStatus() {
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
    camera.centerY = sin(Utils::degToRad(camera.XZAngle));
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
    resetKeyStatus();

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

    glPushMatrix();
    glTranslatef(x, y, z);

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

    glPopMatrix();
    glPopAttrib();
}

void defineLight() {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    GLfloat ambient[] = {0, 0, 0, 1};
    GLfloat diffuse[] = {1, 1, 1, 1};
    GLfloat specular[] = {1, 1, 1, 1};

    if (nightMode) {
        GLfloat cutoff[] = {35};

// ------------------ LIGHT 1 ---------------------
        pos pos1 = mp1.getLightPos();
        pos target1 = mp1.getLightTarget();
        GLfloat light1Position[] = {pos1.x, pos1.y, pos1.z, 1};
        GLfloat light1Target[] = {target1.x - pos1.x, target1.y - pos1.y, target1.z - pos1.z};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1Target);
        glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

// ------------------ LIGHT 2 ---------------------
        pos pos2 = mp2.getLightPos();
        pos target2 = mp2.getLightTarget();
        GLfloat light2Position[] = {pos2.x, pos2.y, pos2.z, 1};
        GLfloat light2Target[] = {target2.x - pos2.x, target2.y - pos2.y, target2.z - pos2.z};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2Target);
        glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);

        if (drawLights) {
            glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0, 1.0, 0.0);
            glBegin(GL_POINTS);
            glVertex3f(light1Position[0], light1Position[1], light1Position[2]);
            glVertex3f(light2Position[0], light2Position[1], light2Position[2]);
            glEnd();
            glEnable(GL_LIGHTING);
        }
    } else {
        GLfloat cutoff[] = {180};

// ------------------ LIGHT 0 ---------------------
        GLfloat lightPosition[] = {arena.x + (arena.width / 2), 2 * 120, arena.z + (arena.height / 2), 1};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

        if (drawLights) {
            glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0, 1.0, 0.0);
            glBegin(GL_POINTS);
            glVertex3f(lightPosition[0], lightPosition[1], lightPosition[2]);
            glEnd();
            glEnable(GL_LIGHTING);
        }
    }
}

void enemyDisplay() {
    glViewport(0, HEIGHT_MAIN, WIDTH, HEIGHT_ENEMY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat) WIDTH / (GLfloat) HEIGHT_ENEMY, 15, 10000);
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
    glViewport(0, 0, WIDTH, HEIGHT_MAIN);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (camera.state == 1) {
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
        camera.eyeY = camera.r * sin(Utils::degToRad(camera.XYAngle)) + target.y;
        camera.eyeZ = camera.r * sin(Utils::degToRad(camera.XZAngle)) * cos(Utils::degToRad(camera.XYAngle)) + target.z;

        gluLookAt(camera.eyeX, camera.eyeY, camera.eyeZ, camera.centerX, camera.centerY, camera.centerZ, camera.upX,
                  camera.upY, camera.upZ);
    }

    defineLight();

    if (axes) {
        drawAxes(50, arena.x, 0, arena.z);
    }


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
    enemyDisplay();

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
                mp2.walk(0.5 * timeDifference, mp1, arena);
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
    glutInitWindowSize(WIDTH, HEIGHT_MAIN + HEIGHT_ENEMY);
    glutInitWindowPosition(1100, 100);
    glutCreateWindow("T3");

    if (argc < 2) {
        printf("MISSING ARENA FILE\n");
        return 0;
    }
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