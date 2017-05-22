#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
{
   setFocusPolicy(Qt::StrongFocus);
}

void MyGLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glEnable(GL_DEBUG_OUTPUT);

    QOpenGLDebugLogger *debugLogger = new QOpenGLDebugLogger(this);
    connect(debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)), this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if(debugLogger->initialize()){
        debugLogger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
        debugLogger->enableMessages();
    }

    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);

    f->glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    f->glClearDepthf(1.0f);
    f->glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/default330.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/default330.frag");

    initializeComponents();
    initializeVertices();
    initializeVBO();
}

void MyGLWidget::paintGL()
{
    QOpenGLExtraFunctions *extf = QOpenGLContext::currentContext()->extraFunctions();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    matrix.ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);
    matrix.translate(0.0f, 0.0f, -1.0f);

    if(flag){
            glRotatef(counter, 0.0f, 1.0f, 0.0f);
        }

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

    int uniformMatrix = 0;
    uniformMatrix = shaderProgram.uniformLocation("matrix");
    shaderProgram.setUniformValue(uniformMatrix, matrix);

    shaderProgram.setAttributeBuffer(attrVertices, GL_FLOAT, 0, 4, sizeof(GLfloat) * 8);
    shaderProgram.setAttributeBuffer(attrColors, GL_FLOAT, sizeof(GLfloat) * 4, 4, sizeof(GLfloat) * 8);

    f->glDrawElements(GL_QUADS, 24, GL_FLOAT, (GLvoid*)NULL);

    shaderProgram.disableAttributeArray(attrVertices);
    shaderProgram.disableAttributeArray(attrColors);

    vbo.release();
    ibo.release();

    if(flag){
            this->update();
            counter++;
        }

}


void MyGLWidget::resizeGL(int w, int h)
{
    x = (400 + 1)*(w / 2) + 0;
    y = (400 + 1)*(h / 2) + 0;
    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.05, 0.05, -0.05, 0.05, 0.1, 100.0);
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
    moveZ = -7.0f;
    rotationAngle = 0.0f;
    rotationX = 0.0f;
    rotationY = 0.0f;
    rotationZ = 0.0f;
}


void MyGLWidget::initializeVertices()
{
    vertices[0][0] = -0.5f;     vertices[0][1] = -0.5f; vertices[0][2] = 0.5f;  vertices[0][3] = 1.0f;  vertices[0][4] = 1.0f;  vertices[0][5] = 0.0f;   vertices[0][6] = 0.0f; vertices[0][7] = 1.0f;
    vertices[1][0] = 0.5f;      vertices[1][1] = -0.5f; vertices[1][2] = 0.5f;  vertices[1][3] = 1.0f;  vertices[1][4] = 0.0f;  vertices[1][5] = 1.0f;   vertices[1][6] = 0.0f; vertices[1][7] = 1.0f;
    vertices[2][0] = 0.5f;      vertices[2][1] = 0.5f;  vertices[2][2] = 0.5f;  vertices[2][3] = 1.0f;  vertices[2][4] = 0.0f;  vertices[2][5] = 0.0f;   vertices[2][6] = 1.0f; vertices[2][7] = 1.0f;
    vertices[3][0] = -0.5f;     vertices[3][1] = 0.5f;  vertices[3][2] = 0.5f;  vertices[3][3] = 1.0f;  vertices[3][4] = 0.0f;  vertices[3][5] = 1.0f;   vertices[3][6] = 1.0f; vertices[3][7] = 1.0f;

    vertices[4][0] = -0.5f;     vertices[4][1] = -0.5f; vertices[4][2] = -0.5f; vertices[4][3] = 1.0f;  vertices[4][4] = 1.0f;  vertices[4][5] = 1.0f;   vertices[4][6] = 0.0f; vertices[4][7] = 1.0f;
    vertices[5][0] = 0.5f;      vertices[5][1] = -0.5f; vertices[5][2] = -0.5f; vertices[5][3] = 1.0f;  vertices[5][4] = 1.0f;  vertices[5][5] = 0.0f;   vertices[5][6] = 1.0f; vertices[5][7] = 1.0f;
    vertices[6][0] = 0.5f;      vertices[6][1] = 0.5f;  vertices[6][2] = -0.5f; vertices[6][3] = 1.0f;  vertices[6][4] = 1.0f;  vertices[6][5] = 1.0f;   vertices[6][6] = 1.0f; vertices[6][7] = 1.0f;
    vertices[7][0] = -0.5f;     vertices[7][1] = 0.5f;  vertices[7][2] = -0.5f; vertices[7][3] = 1.0f;  vertices[7][4] = 1.0f;  vertices[7][5] = 0.5f;   vertices[7][6] = 1.0f; vertices[7][7] = 1.0f;


    indices[0] = 4;
    indices[1] = 0;
    indices[2] = 3;
    indices[3] = 7;

    indices[4] = 0;
    indices[5] = 1;
    indices[6] = 2;
    indices[7] = 3;

    indices[8] = 1;
    indices[9] = 5;
    indices[10] = 6;
    indices[11] = 2;

    indices[12] = 5;
    indices[13] = 4;
    indices[14] = 7;
    indices[15] = 6;

    indices[16] = 3;
    indices[17] = 2;
    indices[18] = 6;
    indices[19] = 7;

    indices[20] = 4;
    indices[21] = 5;
    indices[22] = 1;
    indices[23] = 0;
}

void MyGLWidget::initializeVBO()
{
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(&vertices, sizeof(GLfloat) * 8 * 8);
    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.allocate(&indices, sizeof(GLubyte) * 24);
    ibo.release();
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

    if(wheel >= -5 && wheel <= 5)
    {
        if(deltaValue < 0){
            moveZ++;
            wheel++;
        }
        else if(deltaValue > 0){
            moveZ--;
            wheel--;
        }else{

        }

        if(wheel == -6){
            moveZ++;
            wheel++;
        }
        if(wheel == 6){
            moveZ--;
            wheel--;
        }

        emit wheelValueForZChanged(wheel);
        this->update(); // Widges wird upgedated
    }

    event->accept();
}


void MyGLWidget::receiveRotationX(int angle)
{
    rotationAngle = angle;
    rotationX = 1.0f;
    rotationY = 0.0f;
    rotationZ = 0.0f;
    this->update();
}

void MyGLWidget::receiveRotationY(int angle)
{
    rotationAngle = angle;
    rotationX = 0.0f;
    rotationY = 1.0f;
    rotationZ = 0.0f;
    this->update();
}

void MyGLWidget::receiveRotationZ(int angle)
{
    rotationAngle = angle;
    rotationX = 0.0f;
    rotationY = 0.0f;
    rotationZ = 1.0f;
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
