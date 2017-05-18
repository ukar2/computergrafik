#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer)
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

    setFocusPolicy(Qt::StrongFocus);
}

void MyGLWidget::initializeGL()
{
    QOpenGLDebugLogger *debugLogger = new QOpenGLDebugLogger(this);
    connect(debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)), this, SLOT(onMessageLogged(QOpenGLDebugMessage)), Qt::DirectConnection);

    if(debugLogger->initialize()){
        debugLogger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
        debugLogger->enableMessages();
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearDepth(1.0f);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    initVetices();
    init();
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vbo.bind();
    ibo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glEnable(GL_VERTEX_ARRAY);
    f->glEnable(GL_COLOR_ARRAY);
    f->glVertexAttribPointer(0, 4, GL_FLOAT, true, sizeof(GLfloat) * 8, (char*)NULL + 0);


    if(flag){

    }
//GLint size, GLenum type, GLsizei strite

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(4, GL_FLOAT, sizeof(GLfloat) * 8, (char*)NULL + 0);
    glColorPointer(4, GL_FLOAT, sizeof(GLfloat) * 8, (char*)NULL + sizeof(GLfloat) * 4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);


    glDrawArrays(GL_TRIANGLES, 0, 4);
    glFlush();

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
    qDebug() << message;
}


void MyGLWidget::initVetices()
{
    // 1. Vertex, Position
    vertices[0] = 1.0f;
    vertices[1] = -1.0f;
    vertices[2] = -7.0f;
    vertices[3] = 1.0f;

    // 1. Vertex, Color
    vertices[4] = 1.0f;
    vertices[5] = 0.0f;
    vertices[6] = 0.0f;
    vertices[7] = 1.0f;

    // 2. Vertex, Position
    vertices[8] = 1.0f;
    vertices[9] = 1.0f;
    vertices[10] = -7.0f;
    vertices[11] = 1.0f;

    // 2. Vertex, Color
    vertices[12] = 0.0f;
    vertices[13] = 1.0f;
    vertices[14] = 0.0f;
    vertices[15] = 1.0f;

    // 3. Vertex, Position
    vertices[16] = -1.0f;
    vertices[17] = 1.0f;
    vertices[18] = -7.0f;
    vertices[19] = 1.0f;

    // 3. Vertex, Color
    vertices[20] = 0.0f;
    vertices[21] = 0.0f;
    vertices[22] = 1.0f;
    vertices[23] = 1.0f;

    // 4. Vertex, Position
    vertices[8] = -1.0f;
    vertices[9] = -1.0f;
    vertices[10] = 0.0f;
    vertices[11] = 1.0f;

    // 4. Vertex, Color
    vertices[12] = 1.0f;
    vertices[13] = 1.0f;
    vertices[14] = -7.0f;
    vertices[15] = 1.0f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;
}

void MyGLWidget::init()
{
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(vertices, sizeof(GLfloat) * 4 * 8);

    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.allocate(indices, sizeof(GLubyte) * 6);
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
