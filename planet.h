#ifndef PLANET_H
#define PLANET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include <QMatrix4x4>
#include <QImage>

#include <string>
#include <map>

#include "modelloader.h"

using namespace std;

enum Name{
    Sun,
    Mercury,
    Venus,
    Earth,
    Mars,
    Jupiter,
    Saturn,
    Uranus,
    Neptune,
    Moon,
    Phobos,
    Deimos
};

class Planet
{
public:
    Planet();
    Planet(Name name);
    Planet(Planet *name);

    Name p_name;
    Planet *child;
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
    void rendern();
    void draw();
    void resize();

private:
    QOpenGLTexture *qTex;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vbo, ibo;

    QMatrix4x4 modelMatrix;
    QMatrix4x4 projektionMatrix;
    QMatrix4x4 viewMatrix;


};

#endif // PLANET_H
