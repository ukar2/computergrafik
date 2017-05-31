#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
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
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    initializeDebugLogger();

    // 1. init VBO("sphere_high.obj")
    Planet *p = Planet::getPlanet(Name::Sun);

    // 2. set Texture map
    p->setTextureMap(":/map/sunmap.jpg");

    // 3. shader start
    p->startShaderProgram();

    p->pushToStorage(p);

}



void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Planet *p = Planet::getPlanet(Name::Sun);
    p->rendern();

    if(flag){
        this->update();
        counter++;
        qDebug() << counter;
    }

}


void MyGLWidget::resizeGL(int w, int h)
{
    GLint x = (w / 2) - 612;
    GLint y = (h / 2) - 384;

    // Projektion-Matrix macht aus der 3D-Welt ein 2D-Bild.
    //projektionMatrix.setToIdentity();
    //projektionMatrix.frustum(-0.05f, 0.05f, -0.05f, 0.05f, 0.1f, 1000.0f);
    Planet *p = Planet::getPlanet(Name::Sun);
    p->resize();
    glViewport(x, y, w, h);
}



void MyGLWidget::initializeComponents()
{
    flag = false;
    counter = 0.0f;
    wheel = 0;
    moveX = 0.0f;
    moveY = 0.0f;
    moveZ = -7.0f;
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
        moveX++;
        break;
    case 68:
        moveX--;
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


    if(deltaValue < 0){
        moveZ--;
        wheel--;
    }
    else if(deltaValue > 0){
        moveZ++;
        wheel++;
    }else{

    }

    emit wheelValueForZChanged(wheel);  // change Spin-Box value
    event->accept();
    this->update(); // Widge update -> painGL()
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
    //vbo.release();
    //ibo.release();

    //shaderProgram.release();
    //if(!vboData)
      //  delete vboData;
    //if(!indexData)
      //  delete indexData;

    //glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
}
