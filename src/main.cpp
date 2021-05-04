#include <cmath>
#include <iostream>
#include <cstdlib>
#include "tinyxml/tinystr.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <GL/glut.h>
#include "tinyxml/tinyxml.h"
#include "polygons/Rectangle.h"
#include "polygons/Circle.h"
#include "objects/Player.h"
#include "objects/Arena.h"
#include "input/Mouse.h"
#include "model/Model.h"
#include "objects/ModelPlayer.h"

#include <unistd.h>


int keyStatus[256];
Mouse mouse, p2Mouse;

GLdouble Width;
GLdouble Height;

Arena arena;
Player p1, p2;
ModelPlayer mp1, mp2;
Model m;

bool gameOver = false;

void initialize(char *const fileName) {
    TiXmlDocument doc(fileName);
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("\n%s:\n", fileName);
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
            Width = std::stod(element->Attribute("width"));
            Height = std::stod(element->Attribute("height"));

            arena.initializeArena(
                    std::stof(element->Attribute("x")),
                    std::stof(element->Attribute("y")),
                    std::stof(element->Attribute("height")),
                    std::stof(element->Attribute("width")),
                    element->Attribute("fill")
            );

            printf("%s %s %s %s %s %s\n",
                   tag.c_str(), element->Attribute("x"), element->Attribute("y"),
                   element->Attribute("width"), element->Attribute("height"), element->Attribute("fill")
            );
        } else if (tag == "circle" && p1Color == element->Attribute("fill")) {
            cy1 = arena.y + (arena.y + arena.height) - std::stof(element->Attribute("cy"));
            p1.initializePlayer(
                    std::stof(element->Attribute("cx")),
                    cy1, 0,
                    std::stof(element->Attribute("r")),
                    element->Attribute("fill")
            );

            printf("p1 %s %s %s %s %s\n",
                   tag.c_str(), element->Attribute("cx"), element->Attribute("cy"),
                   element->Attribute("r"), element->Attribute("fill")
            );
        } else if (tag == "circle") {
            cy1 = arena.y + (arena.y + arena.height) - std::stof(element->Attribute("cy"));
            p2.initializePlayer(
                    std::stof(element->Attribute("cx")),
                    cy1, 0,
                    std::stof(element->Attribute("r")),
                    element->Attribute("fill")
            );

            printf("p2 %s %s %s %s %s\n",
                   tag.c_str(), element->Attribute("cx"), element->Attribute("cy"),
                   element->Attribute("r"), element->Attribute("fill")
            );
        }
    }

    double deg = Utils::radToDeg(std::atan2(p1.getY() - p2.getY(), p1.getX() - p2.getX()));
    p1.setAngle(deg + 180);
    p2.setAngle(deg);
}

static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;

void showScore(GLfloat x, GLfloat y) {
    glColor3f(1, 0, 0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "Jogador: %d Computador: %d", p1.getScore(), p2.getScore());
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while (*tmpStr) {
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void showGameOver(GLfloat x, GLfloat y) {
    glColor3f(1, 0, 0);
    //Cria a string a ser impressa
    char *tmpStr;
    if (p1.getScore() >= 10) {
        sprintf(str, "VOCE GANHOU");
    } else {
        sprintf(str, "VOCE PERDEU");
    }
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while (*tmpStr) {
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
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
        case 'n':
        case 'N':
        case 27:
            exit(0);
        case ' ':
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
    mouse.movedX = (GLfloat) x + arena.x;
    mouse.movedY = arena.y + arena.height - (GLfloat) y;

    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
    mouse.button = button;
    mouse.state = state;
    mouse.clickX = (GLfloat) x + arena.x;
    mouse.clickY = arena.y + arena.height - (GLfloat) y;

    motion(x, y);
}

void init() {
    mouse.state = p2Mouse.state = 1;
    mouse.justClicked = false;
    ResetKeyStatus();

    m.initialize();
    mp1.initialize(m);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glDepthFunc(GL_LEQUAL);
}

void reshape(int w, int h) {
    //Ajusta o tamanho da tela com a janela de visualizacao
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        gluPerspective(45, (GLfloat) h / (GLfloat) w, 1, 1000);
    } else {
        gluPerspective(45, (GLfloat) w / (GLfloat) h, 1, 1000);
    }
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

void display() {
    glClearColor(102.0 / 255.0, 153.0 / 255.0, 153.0 / 255.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(400, 400, 400, 0, 0, 0, 0, 1, 0);

    drawAxes(50, 0, 0, 0);

    if (!gameOver) {
        mp1.draw();
    } else {
        showGameOver(arena.x + arena.width / 2, arena.y + arena.height / 2);
    }

    glutSwapBuffers();
}

void idle() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    static GLdouble punchTime = 0;
    static GLdouble punchVelocity = Width / 700;
    static bool increasing = true;
    GLdouble currentTime, timeDifference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;

    if (!keyStatus[(int) (' ')] && false) {
        if (increasing) {
            punchTime += timeDifference;
        } else {
            punchTime -= timeDifference;
        }

        if (punchTime < -700 || punchTime > 700) {
            increasing = !increasing;
            p2Mouse.state = 0;
        }
        double p2X = p2.getX();
        double p2Y = p2.getY();
        p2Mouse.button = 0;
        p2Mouse.clickX = 0;
        p2Mouse.movedX = punchTime * punchVelocity;
        p2.walk(0.1 * timeDifference, p1, arena);
        p2.setAngle(Utils::radToDeg(std::atan2(p1.getY() - p2.getY(), p1.getX() - p2.getX())));
        if (p2X != p2.getX() || p2Y != p2.getY()) {
            p2Mouse.state = 1;
        }
    } else {
        p2Mouse.state = 1;
    }
    if(mp1.ready()) {
        if (keyStatus[(int) ('w')]) {
            mp1.walk(timeDifference);
        }
        if (keyStatus[(int) ('s')]) {
            mp1.walk(-timeDifference);
        }
        if (keyStatus[(int) ('a')]) {
            mp1.rotate(timeDifference);
        }
        if (keyStatus[(int) ('d')]) {
            mp1.rotate(-timeDifference);
        }
        if (keyStatus[(int) ('q')]) {
            mp1.startPunch();
        }
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    initialize(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Create window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("T3");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);

    glutMotionFunc(motion);
    glutMouseFunc(mouseFunc);

    glutMainLoop();

    return 0;
}