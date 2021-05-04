//
// Created by otavio on 03/05/2021.
//

#ifndef T3_MODEL_H
#define T3_MODEL_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <cstring>

typedef struct POS {
    float x;
    float y;
    float z;
} pos;

typedef struct NORM {
    float x;
    float y;
    float z;
} norm;

typedef struct TEX {
    float u;
    float v;
} tex;

typedef struct VERTICE_STRIP {
    pos vPos;
    norm vNorm;
    tex vTex;
} verticeStrip;

class Frame {
public:
    std::vector<pos> vertsPos;         //Lista de posicao dos vertices (original do OBJ)
    std::vector<norm> vertsNorm;       //Lista de normais dos vertices (original do OBJ)
    std::vector<tex> vertsTex;         //Lista de coor de textura dos vertices (original do OBJ)
    std::vector<verticeStrip> vertsS;  //Lista ordenada de vertices das faces para o desenho do modelo via trangle strip
    int changeTexture;
};

class Material {
public:
    GLfloat materialAmbient[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat materialDiffuse[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat materialSpecular[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat materialEmission[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat materialShininess[1] = {180.0};
    GLuint texture0{};
    GLuint texture1{};
};

class Model {
public:
    Frame idle;
    std::vector<Frame> punch;
    std::vector<Frame> fwalk;
    std::vector<Frame> bwalk;
    Material material;

    void initialize();
    void draw(Frame &frame);

private:
    bool loadMesh(const char *path, Frame &frame);  //Path é o caminho para o arquivo .obj e deve conter o nome do arquivo.obj
    GLuint loadTexture(const char *filename);
};


#endif //T3_MODEL_H
