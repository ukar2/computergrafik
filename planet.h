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
};

#endif // PLANET_H
