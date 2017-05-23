#include "planet.h"

Planet::Planet()
{

}

void Planet::set_qTex(QOpenGLTexture* qTex)
{
    this->qTex = qTex;
}

void Planet::set_iboLength(unsigned int iboLength)
{
    this->iboLength = iboLength;
}
