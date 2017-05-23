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


    // --- Shader: Vertex, Fragment ---

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/default330.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/default330.frag");
    shaderProgram.link();

    // --- end.

    initializeVBO();  // Vertex- und Indexdata (Array) ins Buffer laden
}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Die Model-Matrix speichert wie das 3d Objekt aus den Buffern translatiert/rotiert werden soll(ohne Einfluss auf die Welt).
    modelMatrix.setToIdentity();
    modelMatrix.translate(moveX, moveY, moveZ);
    modelMatrix.rotate(rotationAngleX, 1.0f, 0.0f, 0.0f);
    modelMatrix.rotate(rotationAngleY, 0.0f, 1.0f, 0.0f);
    modelMatrix.rotate(rotationAngleZ, 0.0f, 0.0f, 1.0f);

    // Die View-Matrix speichert wie die Welt translatiert/rotiert werden soll (hat Einfluss auf alle Objekte in der Welt).
    viewMatrix.setToIdentity();
    //viewMatrix.translate(0.0f, 0.0f, -15.0f);
    //viewMatrix.rotate(0.0f, 1.0f, 0.0f, 0.0f);
    //viewMatrix.rotate(0.0f, 0.0f, 1.0f, 0.0f);
    //viewMatrix.rotate(0.0f, 0.0f, 0.0f, 1.0f);

    shaderProgram.bind();
    vbo.bind();
    ibo.bind();

    // definiere die Schnittstelle fuer die Eckpunkte
    int attrVertices = 0;
    int attrColors = 1;
    attrVertices = shaderProgram.attributeLocation("vert");
    attrColors = shaderProgram.attributeLocation("color");

    shaderProgram.enableAttributeArray(attrVertices);
    shaderProgram.enableAttributeArray(attrColors);

    int pMatrix = 0;
    pMatrix = shaderProgram.uniformLocation("projektionMatrix");
    shaderProgram.setUniformValue(pMatrix, projektionMatrix);

    int vMatrix = 1;
    vMatrix = shaderProgram.uniformLocation("viewMatrix");
    shaderProgram.setUniformValue(vMatrix, viewMatrix);

    int mMatrix = 2;
    mMatrix = shaderProgram.uniformLocation("modelMatrix");
    shaderProgram.setUniformValue(mMatrix, modelMatrix);


    shaderProgram.setAttributeBuffer(attrVertices, GL_FLOAT, 0, 4, sizeof(GLfloat) * 8);
    shaderProgram.setAttributeBuffer(attrColors, GL_FLOAT, sizeof(GLfloat) * 4, 4, sizeof(GLfloat) * 8);

    f->glDrawElements(GL_QUADS, iboLength, GL_UNSIGNED_INT, (GLvoid*)NULL);

    shaderProgram.disableAttributeArray(attrVertices);
    shaderProgram.disableAttributeArray(attrColors);

    vbo.release();
    ibo.release();

    shaderProgram.release();

    if(flag){
            //this->update();
            //counter++;
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


void MyGLWidget::initializeVBO()
{
    // --- Model ---


    ModelLoader model;
    bool res = model.loadObjectFromFile("C:/Users/rempel/qtworkspace/CG-Praktikum/Model/sphere_high.obj");

    if(res)
    {
        vboLength = model.lengthOfSimpleVBO(0);
        iboLength = model.lengthOfIndexArray();

        vboData = new GLfloat[vboLength];
        indexData = new GLuint[iboLength];
        model.genSimpleVBO(vboData);
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
