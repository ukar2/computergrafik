#ifndef PLANET_H
#define PLANET_H

#include <QOpenGLTexture>
#include <QOpenGLBuffer>

class Planet
{
public:
    Planet();

    void set_qTex(QOpenGLTexture *qTex);
    void set_iboLength(unsigned int iboLength);

    unsigned int iboLength;
    QOpenGLTexture* qTex;

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

};

#endif // PLANET_H
