#include <iostream>
#include <cstdlib>
#include "tinyxml/tinystr.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "tinyxml/tinyxml.h"
#include "polygons/Rectangle.h"
#include "polygons/Circle.h"
#include "objects/Player.h"
#include "objects/Arena.h"

int keyStatus[256];

GLdouble Width;
GLdouble Height;

Arena arena;
Player p1, p2;

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


    bool p1Settings = true;
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
        } else if (tag == "circle" && p1Settings) {
            p1Settings = false;
            p1.initializePlayer(
                    std::stof(element->Attribute("cx")),
                    std::stof(element->Attribute("cy")), 0,
                    std::stof(element->Attribute("r")),
                    element->Attribute("fill")
            );

            printf("p1 %s %s %s %s %s\n",
                   tag.c_str(), element->Attribute("cx"), element->Attribute("cy"),
                   element->Attribute("r"), element->Attribute("fill")
            );
        } else if (tag == "circle") {
            p2.initializePlayer(
                    std::stof(element->Attribute("cx")),
                    std::stof(element->Attribute("cy")), 180,
                    std::stof(element->Attribute("r")),
                    element->Attribute("fill")
            );

            printf("p2 %s %s %s %s %s\n",
                   tag.c_str(), element->Attribute("cx"), element->Attribute("cy"),
                   element->Attribute("r"), element->Attribute("fill")
            );
        }

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
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y) {
    keyStatus[(int) (key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus() {
    for (int i = 0; i < 256; i++) {
        keyStatus[i] = 0;
    }
}

void init() {
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

    p1.draw();
    p2.draw();

    glutSwapBuffers();
}

void idle() {
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    if (keyStatus[(int) ('w')]) {
        p1.walk(timeDiference, p2, arena);
    }
    if (keyStatus[(int) ('s')]) {
        p1.walk(-timeDiference, p2, arena);
    }
    if (keyStatus[(int) ('a')]) {
        p1.rotate(timeDiference);
    }
    if (keyStatus[(int) ('d')]) {
        p1.rotate(-timeDiference);
    }

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

    glutMainLoop();

    return 0;
}
