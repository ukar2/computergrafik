#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMatrix4x4>

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
    //GLfloat rotationX;
    //GLfloat rotationY;
    //GLfloat rotationZ;
    GLfloat rotationAngleX;
    GLfloat rotationAngleY;
    GLfloat rotationAngleZ;

    GLfloat vertices[8][8];
    GLubyte indices[24];

    QOpenGLBuffer vbo, ibo;
    QOpenGLShaderProgram shaderProgram;

    // p*v*m Reihenfolge ist wichtig!!!
    QMatrix4x4 projektionMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 modelMatrix;

    void initializeComponents();
    void initializeVertices();
    void initializeVBO();
};

#endif // MYGLWIDGET_H
