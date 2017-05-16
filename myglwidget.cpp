#include "myglwidget.h"
#include <QDebug>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
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
    GLclampf depth = 1.0f;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // glShadeModel(GL_SMOOTH);  --- deprecated ---
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearDepth(depth);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glMatrixMode(GL_MODELVIEW);  --- deprecated ---
    // glLoadIdentity();               --- deprecated ---
    // glTranslatef(moveX, moveY, moveZ);   --- deprecated ---
    // glRotatef(rotationAngle, rotationX, rotationY, rotationZ);  --- deprecated ---

    if(flag){
        // glRotatef(counter, 0.0f, 1.0f, 0.0f);           --- deprecated ---
    }

    /* --- depricated ---
    glBegin(GL_QUADS);
    // front side
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);        glVertex3f(-1.0f, -1.0f, 1.0f);
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);        glVertex3f(1.0f, -1.0f, 1.0f);
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);        glVertex3f(1.0f, 1.0f, 1.0f);
        glColor4f(0.3f, 0.2f, 0.1f, 1.0f);        glVertex3f(-1.0f, 1.0f, 1.0f);
    // left side
        glColor4f(0.3f, 0.5f, 0.7f, 1.0f);        glVertex3f(-1.0f, -1.0f, -1.0f);
        glColor4f(0.3f, 0.5f, 0.7f, 1.0f);        glVertex3f(-1.0f, -1.0f, 1.0f);
        glColor4f(0.3f, 0.5f, 0.7f, 1.0f);        glVertex3f(-1.0f, 1.0f, 1.0f);
        glColor4f(0.3f, 0.5f, 0.7f, 1.0f);        glVertex3f(-1.0f, 1.0f, -1.0f);
    // back side
        glColor4f(0.7f, 0.5f, 0.2f, 1.0f);        glVertex3f(1.0f, -1.0f, -1.0f);
        glColor4f(0.7f, 0.5f, 0.2f, 1.0f);        glVertex3f(-1.0f, -1.0f, -1.0f);
        glColor4f(0.7f, 0.5f, 0.2f, 1.0f);        glVertex3f(-1.0f, 1.0f, -1.0f);
        glColor4f(0.7f, 0.5f, 0.2f, 1.0f);        glVertex3f(1.0f, 1.0f, -1.0f);
    // right side
        glColor4f(0.1f, 0.4f, 0.7f, 1.0f);        glVertex3f(1.0, -1.0,  1.0);
        glColor4f(0.1f, 0.4f, 0.7f, 1.0f);        glVertex3f(1.0, -1.0, -1.0);
        glColor4f(0.1f, 0.4f, 0.7f, 1.0f);        glVertex3f(1.0,  1.0, -1.0);
        glColor4f(0.1f, 0.4f, 0.7f, 1.0f);        glVertex3f(1.0,  1.0,  1.0);
    // on the top
        glColor4f(0.5f, 0.1f, 0.5f, 1.0f);        glVertex3f(-1.0,  1.0, 1.0);
        glColor4f(0.5f, 0.1f, 0.5f, 1.0f);        glVertex3f(1.0,  1.0,  1.0);
        glColor4f(0.5f, 0.1f, 0.5f, 1.0f);        glVertex3f(1.0,  1.0,  -1.0);
        glColor4f(0.5f, 0.1f, 0.5f, 1.0f);        glVertex3f(-1.0,  1.0, -1.0);
    // on the bottom
        glColor4f(0.5f, 0.1f, 0.8f, 1.0f);        glVertex3f( -1.0, -1.0, 1.0);
        glColor4f(0.5f, 0.1f, 0.8f, 1.0f);        glVertex3f(  -1.0, -1.0, -1.0);
        glColor4f(0.5f, 0.1f, 0.8f, 1.0f);        glVertex3f(  1.0, -1.0, -1.0);
        glColor4f(0.5f, 0.1f, 0.8f, 1.0f);        glVertex3f( 1.0, -1.0,  1.0);
    glEnd();*/

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
    // glMatrixMode(GL_PROJECTION);     --- deprecated ---
    // glLoadIdentity();                --- deprecated ---
    // glFrustum(-0.05, 0.05, -0.05, 0.05, 0.1, 100.0);     --- deprecated ---
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

}
