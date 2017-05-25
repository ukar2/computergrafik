#ifndef PLANET_H
#define PLANET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include <QImage>

#include <string>

using namespace std;

class Planet
{
public:
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
    } name;

    Planet(Name planet);
    ~Planet();

    bool addTextureMap(string path = "");
    void releaseTexture();
    void bindTexture(QOpenGLShaderProgram *shaderProgram, string texture);

private:
    QOpenGLTexture *qTex;

};

#endif // PLANET_H
