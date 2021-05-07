//
// Created by otavio on 03/05/2021.
//

#include "Model.h"
#include "Image.h"


void Model::initialize() {
    printf("loading model texture\n");
    material.texture0 = loadTexture("../resources/Ch44_1002_Diffuse.bmp");
    material.texture1 = loadTexture("../resources/Ch44_1001_Diffuse.bmp");

    loadMesh("../resources/idle.obj", idle);

    Frame aux;

    printf("loading model mesh\n");
    loadMesh("../resources/walking/walking_000001.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000002.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000003.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000004.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000005.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000006.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000007.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000008.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000009.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000010.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000011.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000012.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000013.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000014.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000015.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000016.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000017.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000018.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000019.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000020.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000021.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000022.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000023.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000024.obj", aux);
    fwalk.push_back(aux);
    loadMesh("../resources/walking/walking_000025.obj", aux);
    fwalk.push_back(aux);

    for(int i = (int)fwalk.size() - 1; i >= 0; i--) {
        bwalk.push_back(fwalk[i]);
    }

    loadMesh("../resources/punching/punching_000001.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000002.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000003.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000004.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000005.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000006.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000007.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000008.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000009.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000010.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000011.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000012.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000013.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000014.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000015.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000016.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000017.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000018.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000019.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000020.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000021.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000022.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000023.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000024.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000025.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000026.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000027.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000028.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000029.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000030.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000031.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000032.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000033.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000034.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000035.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000036.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000037.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000038.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000039.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000040.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000041.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000042.obj", aux);
    punch.push_back(aux);
    loadMesh("../resources/punching/punching_000043.obj", aux);
    punch.push_back(aux);
}


void Model::draw(Frame &frame) {
    bool first = true;
    glMaterialfv(GL_FRONT, GL_AMBIENT, material.materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, material.materialEmission);
    glMaterialfv(GL_FRONT, GL_SHININESS, material.materialShininess);

    glBindTexture(GL_TEXTURE_2D, material.texture0);
    glColor3f(material.color[0], material.color[1], material.color[2]);


    for (unsigned int i = 0; i < frame.vertsS.size(); i = i + 3) {
        glBegin(GL_TRIANGLE_STRIP);
        for (unsigned int j = i; j < i + 3; j++) {
            glNormal3f(frame.vertsS[j].vNorm.x, frame.vertsS[j].vNorm.y, frame.vertsS[j].vNorm.z);
            glTexCoord2f(frame.vertsS[j].vTex.u, frame.vertsS[j].vTex.v);
            glVertex3f(frame.vertsS[j].vPos.x, frame.vertsS[j].vPos.y, frame.vertsS[j].vPos.z);
        }
        glEnd();

        if (i >= frame.changeTexture && first) {
            first = false;
            glBindTexture(GL_TEXTURE_2D, material.texture1);
        }
    }
}

bool Model::loadMesh(const char *path, Frame &frame) {
    std::vector<int> vertIndex, uvIndex, normIndex;  //indexadores para vertices, mapeamento de textura e normais
    frame.vertsPos.clear();
    frame.vertsNorm.clear();
    frame.vertsTex.clear();
    frame.vertsS.clear();
    int i = 0;
    FILE *file = fopen(path, "r");
    if (file == nullptr) {
        printf("falha ao carregar o arquivo\n");
        return false;
    } else {
        while (true) {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF) {
                break;
            }
            if (strcmp(lineHeader, "v") == 0) {
                pos vert;
                fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
                frame.vertsPos.push_back(vert);
            } else if (strcmp(lineHeader, "vt") == 0) {
                tex vert;
                fscanf(file, "%f %f\n", &vert.u, &vert.v);
                frame.vertsTex.push_back(vert);
            } else if (strcmp(lineHeader, "vn") == 0) {
                norm vert;
                fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
                frame.vertsNorm.push_back(vert);
            } else if (strcmp(lineHeader, "usemtl") == 0) {
                fscanf(file, "%*s\n");
                frame.changeTexture = vertIndex.size();
            } else if (strcmp(lineHeader, "f") == 0) {
                std::string v1, v2, v3;
                unsigned int vertInd[3], uvInd[3], normInd[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertInd[0], &uvInd[0], &normInd[0],
                                     &vertInd[1], &uvInd[1], &normInd[1], &vertInd[2], &uvInd[2], &normInd[2]);
                if (matches != 9) {
                    printf("QUantidade de valores lidos diferente doesperado. Falha ao ler uma linha de face");
                    return false;
                }
                //Cria uma lista com os índices na ordem apropriada para o desenho das faces
                //Esta é a lista de índices de vértices
                vertIndex.push_back(vertInd[0]);
                vertIndex.push_back(vertInd[1]);
                vertIndex.push_back(vertInd[2]);
                //Esta é a lista de índices de mapeamento de textura
                uvIndex.push_back(uvInd[0]);
                uvIndex.push_back(uvInd[1]);
                uvIndex.push_back(uvInd[2]);
                // Esta é a lista de índices de normais
                normIndex.push_back(normInd[0]);
                normIndex.push_back(normInd[1]);
                normIndex.push_back(normInd[2]);
            }
        }
        for (unsigned int i = 0; i < vertIndex.size(); i++) {
            verticeStrip vert;
            vert.vPos.x = frame.vertsPos[vertIndex[i] - 1].x;
            vert.vPos.y = frame.vertsPos[vertIndex[i] - 1].y;
            vert.vPos.z = frame.vertsPos[vertIndex[i] - 1].z;
            vert.vTex.u = frame.vertsTex[uvIndex[i] - 1].u;
            vert.vTex.v = frame.vertsTex[uvIndex[i] - 1].v;
            vert.vNorm.x = frame.vertsNorm[normIndex[i] - 1].x;
            vert.vNorm.y = frame.vertsNorm[normIndex[i] - 1].y;
            vert.vNorm.z = frame.vertsNorm[normIndex[i] - 1].z;
            frame.vertsS.push_back(vert);
        }
    }
    fclose(file);
    return true;
}

GLuint Model::loadTexture(const char *filename) {
    GLuint texture;

    Image *image = Image::loadImage(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB,                       //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,             //GL_UNSIGNED_BYTE, because pixels are stored
            //as unsigned numbers
                 image->pixels);               //The actual pixel data
    delete image;

    return texture;
}
