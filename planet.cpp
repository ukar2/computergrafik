#include "planet.h"


static map<Name, Planet*> storage;


Planet::Planet() : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
    this->p_name = Name::Sun;
    this->parent = NULL;
    initVBO();
}


Planet::Planet(Name name) : vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
    this->p_name = name;
    this->parent = NULL;
    initVBO();
}


void Planet::setPlanetCharacteristics(float axialTilt, float orbDistance, float orbSpeed, float rotationFactor, Planet *parent)
{
    this->parent = parent;
    this->axial_tilt = axialTilt;
    this->orb_distance = orbDistance;
    this->orb_speed = orbSpeed;
    this->rot_factor = rotationFactor;
}

Planet *Planet::getPlanet(Name name)
{
    std::string path = "";
    map<Name, Planet*>::iterator iter = storage.find(name);

    if(iter == storage.end()){
        Planet *p = new Planet(name);

        switch(name){
        case Name::Sun:
            path = ":/map/sunmap.jpg";
            break;
        case Name::Mercury:
            path = ":/map/2k_mercury.jpg";
            break;
        case Name::Venus:
            path = ":/map/2k_venus_atmosphere.jpg";
            break;
        case Name::Earth:
            path = ":/map/2k_earth_daymap.jpg";
            break;
        case Name::Mars:
            path = ":/map/2k_mars.jpg";
            break;
        case Name::Jupiter:
            path = ":/map/2k_jupiter.jpg";
            break;
        case Name::Saturn:
            path = ":/map/2k_saturn.jpg";
            break;
        case Name::Uranus:
            path = ":/map/2k_uranus.jpg";
            break;
        case Name::Neptune:
            path = ":/map/2k_neptune.jpg";
            break;
        case Name::Moon:
            path = ":/map/2k_mercury.jpg";
            break;
        case Name::Phobos:
            path = ":/map/moonmap1k.jpg";
            break;
        case Name::Deimos:
            path = ":/map/moonmap1k.jpg";
            break;
        default:
            qDebug() << "Textur map not found";
            break;
        }

        p->setTextureMap(path);
        return p;

    }else{
        Planet *p = iter->second;
        return p;
    }

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



void Planet::render(QMatrix4x4 vMatrix, float angle)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    viewMatrix = vMatrix;

    if(parent == NULL){
        modelMatrix.setToIdentity();

        modelMatrix.rotate(axial_tilt, 1.0f, 0.0f, 0.0f);
        modelMatrix.rotate(angle, 0.0f, 1.0f, 0.0f);

        draw();

        modelMatrix.rotate(-1.0f * angle, 0.0f, 1.0f, 0.0f);
        modelMatrix.rotate(-1.0f * axial_tilt, 1.0f, 0.0f, 0.0f);

    }else{
        modelMatrix = parent->modelMatrix;
        modelMatrix.rotate(angle * orb_speed, 0.0f, 1.0f, 0.0f);
        modelMatrix.translate(orb_distance, 0.0f, 0.0f);
        modelMatrix.rotate(-1.0f * angle * orb_speed, 0.0f, 1.0f, 0.0f);

        modelMatrix.rotate(axial_tilt, 1.0f, 0.0f, 0.0f);
        modelMatrix.rotate(angle * rot_factor, 0.0f, 1.0f, 0.0f);

        draw();

        modelMatrix.rotate(-1.0f * angle * rot_factor, 0.0f, 1.0f, 0.0f);
        modelMatrix.rotate(-1.0f * axial_tilt, 1.0f, 0.0f, 0.0f);

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

    int attrTexCoords = 1;
    attrTexCoords = shaderProgram.attributeLocation("texCoord");


    shaderProgram.enableAttributeArray(attrVertices);
    shaderProgram.enableAttributeArray(attrTexCoords);


    //planet.bindTexture(&shaderProgram, "texture");
    qTex->bind();
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
