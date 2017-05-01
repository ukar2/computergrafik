#include "myglwidget.h"


MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    moveX = 0.0f;
    moveY = 0.0f;
    moveZ = -7.0f;
    setFocusPolicy(Qt::StrongFocus);
}

void MyGLWidget::initializeGL()
{
    GLclampf depth = 1.0f;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearDepth(depth);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(moveX, moveY, moveZ);
    glRotatef(40.0f, 0.0f, 1.0f, 0.0f);

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
    glEnd();
    //glFlush();
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.05, 0.05, -0.05, 0.05, 0.1, 100.0);
}

MyGLWidget::~MyGLWidget()
{

}
