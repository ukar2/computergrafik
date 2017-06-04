#ifndef PLANET_H
#define PLANET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include <QMatrix4x4>
#include <QImage>

#include <string>
#include <map>
#include <stack>

#include "modelloader.h"
#include "caddy.h"

using namespace std;


class Planet
{
public:
    Planet();
    Planet(Name name);
    Planet(Planet *name);

    Name p_name;
    Planet *parent;
    GLfloat *vboData;
    GLuint *indexData;
    unsigned int vboLength;
    unsigned int iboLength;

    static Planet *getPlanet(Name name);
    static void pushToStorage(Planet *planet);

    ~Planet();

    void initVBO(); // kann sein in getPlanet besser
    bool setTextureMap(string path = "");
    void bindTexture(QOpenGLShaderProgram *shaderProgram, string texture);
    void releaseTexture();  // kann sein dass alle drei ^ besser in eine
    void startShaderProgram();
    void render(QMatrix4x4 vMatrix, float angle);
    void draw();
    void resize();
    void setPlanetCharacteristics(float axialTilt, float orbDistance, float orbSpeed, float rotationFactor, Planet *parent);

private:
    QOpenGLTexture *qTex;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vbo, ibo;

    QMatrix4x4 modelMatrix;
    QMatrix4x4 projektionMatrix;
    QMatrix4x4 viewMatrix;
    std::stack<QMatrix4x4> matrixStack;

    float orb_speed;
    float rot_factor;
    float orb_distance;
    float axial_tilt;

};

#endif // PLANET_H
