#include "planet.h"


static map<Name, Planet*> storage;


Planet::Planet() : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
    this->p_name = Name::Sun;
    this->child = NULL;
    initVBO();
}


Planet::Planet(Name name) : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
    this->p_name = name;
    this->child = NULL;
    initVBO();
}



Planet::Planet(Planet *name) : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
    this->p_name = name->p_name;
    this->child = name;
    initVBO();
}



Planet *Planet::getPlanet(Name name)
{
    map<Name, Planet*>::iterator iter = storage.find(name);

    if(iter == storage.end()){
        Planet *p = new Planet(name);
        return p;
    }


    /*switch(name){
    case Name::Sun:
        setTextureMap(":/map/sunmap.jpg");
        break;
    case Name::Mercury:
        setTextureMap(":/map/mercurybump.jpg");
        break;
    case Name::Venus:
        setTextureMap(":/map/2k_venus_atmosphere.jpg");
        break;
    case Name::Earth:
        setTextureMap(":/map/2k_earth_daymap.jpg");
        break;
    case Name::Mars:
        setTextureMap(":/map/2k_mars.jpg");
        break;
    case Name::Jupiter:
        setTextureMap(":/map/2k_jupiter.jpg");
        break;
    case Name::Saturn:
        setTextureMap(":/map/2k_saturn.jpg");
        break;
    case Name::Uranus:
        setTextureMap(":/map/2k_uranus.jpg");
        break;
    case Name::Neptune:
        setTextureMap(":/map/2k_neptune.jpg");
        break;
    }*/

    return iter->second;
    //return p;
}



void Planet::pushToStorage(Planet *planet)
{
    map<Name, Planet*>::iterator iter = storage.find(planet->p_name);

    if(iter == storage.end()){
        storage.insert(make_pair(planet->p_name, planet));
    }else{
        storage.erase(planet->p_name);
        storage.insert(make_pair(planet->p_name, planet));
    }
}



void Planet::initVBO()
{
    ModelLoader model;
    bool res = model.loadObjectFromFile("C:/Users/rempel/qtworkspace/CG-Praktikum/Model/sphere_high.obj");

    if(res)
    {
        vboLength = model.lengthOfVBO(0, false, true);
        iboLength = model.lengthOfIndexArray();

        vboData = new GLfloat[vboLength];
        indexData = new GLuint[iboLength];
        model.genVBO(vboData, 0, false, true);
        model.genIndexArray(indexData);
    }else{
        qDebug() << "ModelLoader error ";
    }
    // --- end.


    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate((const void*)vboData, sizeof(GLfloat) * (GLfloat)vboLength);
    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.allocate((const void*)indexData, sizeof(GLuint) * iboLength);
    ibo.release();

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



void Planet::startShaderProgram()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/default330.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/default330.frag");
    shaderProgram.link();
}



void Planet::rendern()
{
    viewMatrix.setToIdentity();
    viewMatrix.translate(0.0f, 0.0f, -7.0f);
    viewMatrix.rotate(0.0f, 1.0f, 0.0f, 0.0f);
    viewMatrix.rotate(0.0f, 0.0f, 1.0f, 0.0f);
    viewMatrix.rotate(0.0f, 0.0f, 0.0f, 1.0f);

   if(child == NULL)
   {
       modelMatrix.setToIdentity();
       modelMatrix.rotate(7.25f, 0.0f, 1.0f, 0.0f);
       draw();
   }else{
       //child->setMatrixSet(projektionMatrix, viewMatrix, modelMatrix);
       qDebug() << "rendern Error";
   }
}


void Planet::draw()
{
    shaderProgram.bind();
    vbo.bind();
    ibo.bind();

    // definiere die Schnittstelle fuer die Eckpunkte
    int attrVertices = 0;
    attrVertices = shaderProgram.attributeLocation("vert");

    int attrTexCoords = 3;
    attrTexCoords = shaderProgram.attributeLocation("texCoord");


    shaderProgram.enableAttributeArray(attrVertices);
    shaderProgram.enableAttributeArray(attrTexCoords);


    //planet.bindTexture(&shaderProgram, "texture");
    qTex->bind(0);
    shaderProgram.setUniformValue("texture", 0);


    int pMatrix = 0;
    pMatrix = shaderProgram.uniformLocation("projektionMatrix");
    shaderProgram.setUniformValue(pMatrix, projektionMatrix);

    int vMatrix = 1;
    vMatrix = shaderProgram.uniformLocation("viewMatrix");
    shaderProgram.setUniformValue(vMatrix, viewMatrix);

    int mMatrix = 2;
    mMatrix = shaderProgram.uniformLocation("modelMatrix");
    shaderProgram.setUniformValue(mMatrix, modelMatrix);


    int offset = 0;
    int stride = 8 * sizeof(GLfloat);

    shaderProgram.setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);
    offset += 4 * sizeof(GLfloat);
    shaderProgram.setAttributeBuffer(attrTexCoords, GL_FLOAT, offset, 4, stride);

    glDrawElements(GL_QUADS, iboLength, GL_UNSIGNED_INT, (GLvoid*)NULL);
    glFlush();

    shaderProgram.disableAttributeArray(attrVertices);
    shaderProgram.disableAttributeArray(attrTexCoords);

    qTex->release();
    vbo.release();
    ibo.release();

    shaderProgram.release();
}



void Planet::resize()
{
    projektionMatrix.setToIdentity();
    projektionMatrix.frustum(-0.05f, 0.05f, -0.05f, 0.05f, 0.1f, 1000.0f);

}


void Planet::releaseTexture()
{
    this->qTex->release();
}


Planet::~Planet()
{
    shaderProgram.release();
    vbo.release();
    ibo.release();

    if(!vboData)
        delete vboData;
    if(!indexData)
        delete indexData;
    if(!qTex)
        delete qTex;
}
