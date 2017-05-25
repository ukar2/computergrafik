#include "planet.h"

Planet::Planet(Name planet)
{
    this->name = planet;
}


bool Planet::addTextureMap(string path)
{
    qTex = new QOpenGLTexture(QImage(path.c_str()).mirrored());

    if(qTex->textureId() != 0){
        qTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        qTex->setMagnificationFilter(QOpenGLTexture::Linear);
        qTex->generateMipMaps(1, true);
        qTex->allocateStorage();
        return true;

    }else{
        return false;
    }
}


void Planet::bindTexture(QOpenGLShaderProgram *shaderProgram, string texture)
{
    shaderProgram->setUniformValue(texture.c_str(), 0);
    this->qTex->bind();
}


void Planet::releaseTexture()
{
    this->qTex->release();
}


Planet::~Planet()
{
    qTex->release();

    if(!qTex)
        delete qTex;
}
