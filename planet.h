#ifndef PLANET_H
#define PLANET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include <QImage>

#include <string>
#include <map>

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
    Name name;

    ~Planet();

    static Planet getPlanet(Name planet);
    static void pushToStorage(Planet planet);

    bool setTextureMap(string path = "");
    void releaseTexture();
    void bindTexture(QOpenGLShaderProgram *shaderProgram, string texture);

private:
    QOpenGLTexture *qTex;

    Planet();
    Planet(Name planet);

};

#endif // PLANET_H
