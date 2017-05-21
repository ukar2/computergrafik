#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>

#include <QDebug>
#include <QOpenGLDebugMessage>
#include <QOpenGLDebugLogger>
#include <QSurface>
#include <QMetaEnum>


class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void receiveRotationX(int);
    void receiveRotationY(int);
    void receiveRotationZ(int);
    void setChkBoxFlag(bool);
    void onMessageLogged(QOpenGLDebugMessage);

signals:
    void wheelValueForZChanged(int value);

private:
    GLint y;
    GLint x;
    GLint wheel;
    bool flag;
    GLfloat counter;
    GLfloat moveX;
    GLfloat moveY;
    GLfloat moveZ;
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    GLfloat rotationAngle;

    GLfloat vertices[8][8];
    GLubyte indices[24];
    //GLuint vboHandle;
    //GLuint indicesHandle;

    QOpenGLBuffer vbo, ibo;
    //QOpenGLContext *m_context;

    void initializeComponents();
    void initializeVertices();
    void initializeVBO();
};

#endif // MYGLWIDGET_H
