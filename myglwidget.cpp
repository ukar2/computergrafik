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

    Caddy caddy;
    // 1. init VBO("sphere_high.obj") && set Texture map
    Planet *sun = Planet::getPlanet(caddy.getNextName());
    sun->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), NULL);
    // 2. start individual shader program for each planet
    sun->startShaderProgram();
    Planet::pushToStorage(sun);


    Planet *mercury = Planet::getPlanet(caddy.getNextName());
    mercury->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    mercury->startShaderProgram();
    Planet::pushToStorage(mercury);


    Planet *venus = Planet::getPlanet(caddy.getNextName());
    venus->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    venus->startShaderProgram();
    Planet::pushToStorage(venus);


    Planet *earth = Planet::getPlanet(caddy.getNextName());
    earth->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    earth->startShaderProgram();
    Planet::pushToStorage(earth);

    Planet *mars = Planet::getPlanet(caddy.getNextName());
    mars->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    mars->startShaderProgram();
    Planet::pushToStorage(mars);


    Planet *jupiter = Planet::getPlanet(caddy.getNextName());
    jupiter->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    jupiter->startShaderProgram();
    Planet::pushToStorage(jupiter);

    Planet *saturn = Planet::getPlanet(caddy.getNextName());
    saturn->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    saturn->startShaderProgram();
    Planet::pushToStorage(saturn);

    Planet *uranus = Planet::getPlanet(caddy.getNextName());
    uranus->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    uranus->startShaderProgram();
    Planet::pushToStorage(uranus);

    Planet *neptune = Planet::getPlanet(caddy.getNextName());
    neptune->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), sun);
    neptune->startShaderProgram();
    Planet::pushToStorage(neptune);

    Planet *moon = Planet::getPlanet(caddy.getNextName());
    moon->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), earth);
    moon->startShaderProgram();
    Planet::pushToStorage(moon);

    Planet *phobos = Planet::getPlanet(caddy.getNextName());
    phobos->setPlanetCharacteristics(caddy.getAxialTilt(), caddy.getOrbDistance(), caddy.getOrbSpeed(), caddy.getRotationFactor(), caddy.getScaleFactor(), mars);
    phobos->startShaderProgram();
    Planet::pushToStorage(phobos);

}



void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewMatrix.setToIdentity();
    viewMatrix.translate(moveX, moveY, moveZ);
    viewMatrix.rotate(rotationAngleX, 1.0f, 0.0f, 0.0f);
    viewMatrix.rotate(rotationAngleY, 0.0f, 1.0f, 0.0f);
    viewMatrix.rotate(rotationAngleZ, 0.0f, 0.0f, 1.0f);

Caddy caddy;


    Planet *sun = Planet::getPlanet(caddy.getNextName());
    sun->render(viewMatrix, counter);


    Planet *mercury = Planet::getPlanet(caddy.getNextName());
    mercury->render(viewMatrix, counter);


    Planet *venus = Planet::getPlanet(caddy.getNextName());
    venus->render(viewMatrix, counter);

    Planet *earth = Planet::getPlanet(caddy.getNextName());
    earth->render(viewMatrix, counter);

    Planet *mars = Planet::getPlanet(caddy.getNextName());
    mars->render(viewMatrix, counter);

    Planet *jupiter = Planet::getPlanet(caddy.getNextName());
    jupiter->render(viewMatrix, counter);

    Planet *saturn = Planet::getPlanet(caddy.getNextName());
    saturn->render(viewMatrix, counter);

    Planet *uranus = Planet::getPlanet(caddy.getNextName());
    uranus->render(viewMatrix, counter);

    Planet *neptune = Planet::getPlanet(caddy.getNextName());
    neptune->render(viewMatrix, counter);

    Planet *moon = Planet::getPlanet(caddy.getNextName());
    moon->render(viewMatrix, counter);

    Planet *phobos = Planet::getPlanet(caddy.getNextName());
    phobos->render(viewMatrix, counter);


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
    Planet *sun = Planet::getPlanet(Name::Sun);
    sun->resize();

    Planet *mercury = Planet::getPlanet(Name::Mercury);
    mercury->resize();

    Planet *venus = Planet::getPlanet(Name::Venus);
    venus->resize();

    Planet *earth = Planet::getPlanet(Name::Earth);
    earth->resize();

    Planet *mars = Planet::getPlanet(Name::Mars);
    mars->resize();

    Planet *jupiter = Planet::getPlanet(Name::Jupiter);
    jupiter->resize();

    Planet *saturn = Planet::getPlanet(Name::Saturn);
    saturn->resize();

    Planet *uranus = Planet::getPlanet(Name::Uranus);
    uranus->resize();

    Planet *neptune = Planet::getPlanet(Name::Neptune);
    neptune->resize();

    Planet *moon = Planet::getPlanet(Name::Moon);
    moon->resize();

    Planet *phobos = Planet::getPlanet(Name::Phobos);
    phobos->resize();


    glViewport(x, y, w, h);
}



void MyGLWidget::initializeComponents()
{
    flag = false;
    counter = 0.0f;
    wheel = 0;
    moveX = 0.0f;
    moveY = 0.0f;
    moveZ = -17.0f;
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
