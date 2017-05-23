#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
   setFocusPolicy(Qt::StrongFocus);
   initializeComponents();
}

void MyGLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glEnable(GL_DEBUG_OUTPUT);
    f->glEnable(GL_TEXTURE_2D);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);

    f->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    f->glClearDepthf(1.0f);
    f->glClearColor(0.1f, 0.2f, 0.3f, 1.0f);


    initializeVBO("sphere_high.obj");           // Vertex- und Indexdata (Array) ins Buffer laden

    addTextureMap(":/map/sunmap.jpg");
    sun.set_qTex(qTex);
    sun.set_iboLength(iboLength);
    qTex->release();

    addTextureMap(":/map/sunmap.jpg");
    mercury.set_qTex(qTex);
    mercury.set_iboLength(iboLength);

    addTextureMap(":/map/sunmap.jpg");
    venus.set_qTex(qTex);
    venus.set_iboLength(iboLength);

    addTextureMap(":/map/earthmap1k.jpg");
    earth.set_qTex(qTex);
    earth.set_iboLength(iboLength);


    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/default330.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/default330.frag");
    shaderProgram.link();

}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::stack<QMatrix4x4> matrixStack;

    // Die Model-Matrix speichert wie das 3d Objekt aus den Buffern translatiert/rotiert werden soll(ohne Einfluss auf die Welt).
    modelMatrix.setToIdentity();
    modelMatrix.translate(0.0f, 0.0f, -7.0f);
    modelMatrix.rotate(rotationAngleX, 1.0f, 0.0f, 0.0f);
    modelMatrix.rotate(rotationAngleY, 0.0f, 1.0f, 0.0f);
    modelMatrix.rotate(rotationAngleZ, 0.0f, 0.0f, 1.0f);
    //modelMatrix.scale(-50.f);


    // Die View-Matrix speichert wie die Welt translatiert/rotiert werden soll (hat Einfluss auf alle Objekte in der Welt).
    viewMatrix.setToIdentity();
    viewMatrix.translate(moveX, moveY, moveZ);
    viewMatrix.rotate(0.0f, 1.0f, 0.0f, 0.0f);
    viewMatrix.rotate(0.0f, 0.0f, 1.0f, 0.0f);
    viewMatrix.rotate(0.0f, 0.0f, 0.0f, 1.0f);

    modelMatrix.setToIdentity();

    matrixStack.push(modelMatrix);                                  //  Matrix sichern

    modelMatrix.rotate(counter * -0.06, 0.0, 1.0, 0.0);         //  Eigenrotation der Sonne

    draw("sun");       //  Rendern der Sonne

    modelMatrix = matrixStack.top();                            //  Merkur

    modelMatrix.rotate(counter * -0.3, 0.0, 1.0, 0.0);          //  Rotation um Zentrum
    modelMatrix.translate(-5.0f, 0.0f, 0.0f);                   //  Translation vom Zentrum
    modelMatrix.scale(0.15f);
    modelMatrix.rotate(counter, 0.0, 1.0, 0.0);                 //  Eigenrotation des Saturn

    drawPlanet(vboSphere, iboSphere, mercury, shaderProgram);   // Rendern des Saturn

    modelMatrix = matrixStack.top();                            //  Venus
    modelMatrix.rotate(counter * -0.2, 0.2, 1.0, 0.0);
    modelMatrix.translate(5.8f, 0.0f, 0.0f);
    modelMatrix.scale(0.5f);
    modelMatrix.rotate(counter, 0.0, 1.0, 0.0);

    drawPlanet(vboSphere, iboSphere, venus, shaderProgram);

    modelMatrix = matrixStack.top();                                //  Erde
    modelMatrix.rotate(counter * -0.3, 0.0, 1.0, 0.0);
    modelMatrix.translate(6.1f, 0.0f, 0.0f);
    modelMatrix.scale(0.43f);
    modelMatrix.rotate(counter * 0.6, 0.0, 1.0, 0.0);

    drawPlanet(vboSphere, iboSphere, earth, shaderProgram);

        modelMatrix.rotate(counter * 0.9, 0.0, 1.0, 0.0);           //  Mond
        modelMatrix.translate(-2.0f, 0.0f, 0.0f);
        modelMatrix.scale(0.3);

        drawPlanet(vboSphere, iboSphere, moon, shaderProgram);



    if(flag){
            this->update();
            counter++;
        }

}


void MyGLWidget::resizeGL(int w, int h)
{
    x = (400 + 1)*(w / 2) + 0;
    y = (400 + 1)*(h / 2) + 0;

    // Projektion-Matrix macht aus der 3d Welt ein 2d Bild.
    projektionMatrix.setToIdentity();
    projektionMatrix.frustum(-0.05f, 0.05f, -0.05f, 0.05f, 0.1f, 1000.0f);
    glViewport(x, y, w, h);
}



void MyGLWidget::initializeVBO(std::string object)
{
    ModelLoader model;
    bool res = model.loadObjectFromFile("C:/Users/rempel/qtworkspace/CG-Praktikum/Model/" + object);

    if(res)
    {
        vboLength = model.lengthOfVBO(0, false, true);
        iboLength = model.lengthOfIndexArray();

        vboData = new GLfloat[vboLength];
        indexData = new GLuint[iboLength];
        model.genVBO(vboData, 0, false, true);
        model.genIndexArray(indexData);
    }else{
        qDebug() << "Model error ";
    }
    // --- end.


    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(vboData, sizeof(GLfloat) * vboLength);
    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.allocate(indexData, sizeof(GLubyte) * iboLength);
    ibo.release();

}


void MyGLWidget::addTextureMap(std::string path)
{
    qTex = new QOpenGLTexture(QImage(path.c_str()).mirrored());

    if(qTex->textureId() != 0){
        qTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        qTex->setMagnificationFilter(QOpenGLTexture::Linear);
    }else{
        qDebug() << "Texture map error ";
    }
}


void MyGLWidget::draw(Planet &planet)
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

    planet.qTex->bind();
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

    glDrawElements(GL_QUADS, planet.iboLength, GL_UNSIGNED_INT, (GLvoid*)NULL);

    shaderProgram.disableAttributeArray(attrVertices);
    shaderProgram.disableAttributeArray(attrTexCoords);

    planet.qTex->release();
    vbo.release();
    ibo.release();

    shaderProgram.release();

}


void MyGLWidget::initializeComponents()
{
    x = 0;
    y = 0;
    flag = false;
    counter = 0.0f;
    wheel = 0;
    moveX = 0.0f;
    moveY = 0.0f;
    moveZ = -5.0f;
    rotationAngleX = 0.0f;
    rotationAngleY = 0.0f;
    rotationAngleZ = 0.0f;
}


void MyGLWidget::initializeDebugLogger()
{
    QOpenGLDebugLogger *debugLogger = new QOpenGLDebugLogger(this);
    connect(debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)), this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if(debugLogger->initialize()){
        debugLogger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
        debugLogger->enableMessages();
    }
}


void MyGLWidget::onMessageLogged(QOpenGLDebugMessage message)
{
    QSurfaceFormat frmt = this->format();
    qDebug().nospace() << "OpenGL: " << frmt.majorVersion() << "." << frmt.minorVersion();
    qDebug().noquote() << "Profile: " << QMetaEnum::fromType<QSurfaceFormat::OpenGLContextProfile>().valueToKey(frmt.profile());
    qDebug().noquote() << "Options: " << QMetaEnum::fromType<QSurfaceFormat::FormatOption>().valueToKeys(frmt.options());
    qDebug().noquote() << "Renderable Type: " << QMetaEnum::fromType<QSurfaceFormat::RenderableType>().valueToKey(frmt.renderableType());
    qDebug().noquote() << "Swap Behavior: " << QMetaEnum::fromType<QSurfaceFormat::SwapBehavior>().valueToKey(frmt.swapBehavior());
    qDebug() << "Swap interval: " << frmt.swapInterval();
    qDebug() << "Debug message: " << message;
}



void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->nativeVirtualKey();
    switch(event->nativeVirtualKey())
    {
    case 87:
        moveY++;
        break;
    case 83:
        moveY--;
        break;
    case 65:
        moveX--;
        break;
    case 68:
        moveX++;
        break;
    case 38:
        moveY++;
        break;
    case 40:
        moveY--;
        break;
    case 37:
        moveX--;
        break;
    case 39:
        moveX++;
        break;
    default:
        event->ignore();
        break;
    }
    this->update();
    event->accept();
}


void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int deltaValue = event->delta();

    //if(wheel >= -5 && wheel <= 5)
    //{
        if(deltaValue < 0){
            moveZ++;
            wheel++;
        }
        else if(deltaValue > 0){
            moveZ--;
            wheel--;
        }else{

        }

        //if(wheel == -6){
            //moveZ++;
            //wheel++;
        //}
        //if(wheel == 6){
          //  moveZ--;
            //wheel--;
        //}

        emit wheelValueForZChanged(wheel);
        this->update(); // Widges wird upgedated
    //}

    event->accept();
}


void MyGLWidget::receiveRotationX(int angle)
{
    rotationAngleX = angle;
    this->update();
}

void MyGLWidget::receiveRotationY(int angle)
{
    rotationAngleY = angle;
    this->update();
}

void MyGLWidget::receiveRotationZ(int angle)
{
    rotationAngleZ = angle;
    this->update();
}


void MyGLWidget::setChkBoxFlag(bool value)
{
    flag = value;
    this->update();
}

MyGLWidget::~MyGLWidget()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    vbo.release();
    ibo.release();
}
