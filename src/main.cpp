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

int keyStatus[256];
Mouse mouse, p2Mouse;

GLdouble Width;
GLdouble Height;

Arena arena;
Player p1, p2;

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
    std::string p1Color = "red";
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
    if(p1.getScore() >= 10) {
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
        case 'y':
        case 'Y':
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

    //TODO: OLHAR DEPOIS
//    if (mouse.justClicked) {
//        mouse.increasing = mouse.movedX > 0;
//    } else if(mouse.increasing && mouse.movedX < -Width/10) {
//        mouse.state = 0;
//        mouse.clickX = (GLfloat) x + arena.x;
//        mouse.clickY = arena.y + arena.height - (GLfloat) y;
//    } else if(mouse.movedX > Width/10) {
//        mouse.state = 0;
//        mouse.clickX = (GLfloat) x + arena.x;
//        mouse.clickY = arena.y + arena.height - (GLfloat) y;
//    }

    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
    mouse.button = button;
    mouse.state = state;
    mouse.clickX = (GLfloat) x + arena.x;
    mouse.clickY = arena.y + arena.height - (GLfloat) y;
//TODO: OLHAR DEPOIS
//    if(button == 0 && state == 0) {
//        mouse.justClicked = true;
//    }

    motion(x, y);
}

void init() {
    mouse.state = p2Mouse.state = 1;
    mouse.justClicked = false;
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION);
    glOrtho(arena.x, arena.x + arena.width, arena.y, arena.y + arena.height, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClearColor(arena.R, arena.G, arena.B, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);

    gameOver = p1.getScore() >= 10 || p2.getScore() >= 10;

    if (!gameOver) {
        p1.draw();
        p2.draw();

        showScore(arena.x + 10, arena.y + 10);
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

    if (!keyStatus[(int) (' ')]) {
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
    if (keyStatus[(int) ('w')]) {
        p1.walk(timeDifference, p2, arena);
        mouse.state = 1;
    }
    if (keyStatus[(int) ('s')]) {
        p1.walk(-timeDifference, p2, arena);
        mouse.state = 1;
    }
    if (keyStatus[(int) ('a')]) {
        p1.rotate(timeDifference);
    }
    if (keyStatus[(int) ('d')]) {
        p1.rotate(-timeDifference);
    }

    p1.treatPunch(timeDifference, mouse, arena, p2);
    p2.treatPunch(timeDifference, p2Mouse, arena, p1);

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    initialize(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //Create window
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("T2");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);

    glutMotionFunc(motion);
    glutMouseFunc(mouseFunc);

    glutMainLoop();

    return 0;
}