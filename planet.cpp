#include "planet.h"


static map<Name, Planet> storage;


Planet Planet::getPlanet(Name name)
{
    map<Name, Planet>::iterator iter = storage.find(name);

    if(iter == storage.end()){
        Planet p(name);
        return p;
    }

    return iter->second;
}


void Planet::pushToStorage(Planet planet)
{
    map<Name, Planet>::iterator iter = storage.find(planet.name);

    if(iter == storage.end()){
        storage.insert(make_pair(planet.name, planet));
    }else{
        storage.erase(planet.name);
        storage.insert(make_pair(planet.name, planet));
    }
}

bool Planet::setTextureMap(string path)
{
    qTex = new QOpenGLTexture(QImage(path.c_str()).mirrored());

    if(qTex->textureId() != 0){
        qTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        qTex->setMagnificationFilter(QOpenGLTexture::Linear);
        //qTex->generateMipMaps(1, true);
        //qTex->allocateStorage();
        return true;

    }else{
        return false;
    }
}


void Planet::bindTexture(QOpenGLShaderProgram *shaderProgram, string texture)
{
    this->qTex->bind();
    shaderProgram->setUniformValue(texture.c_str(), 0);
}


void Planet::releaseTexture()
{
    this->qTex->release();
}

Planet::Planet(Name planet)
{
    this->name = planet;
}


Planet::Planet()
{

}

Planet::~Planet()
{
    /*if(qTex->isBound())
        qTex->release();*/

    if(!qTex)
        delete qTex;
}
