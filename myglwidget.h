#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMatrix4x4>
#include <QImage>

#include <QDebug>
#include <QOpenGLDebugMessage>
#include <QOpenGLDebugLogger>
#include <QSurface>
#include <QMetaEnum>

#include <stack>
#include <string>
#include "modelloader.h"
#include "planet.h"


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
    bool flag;
    //unsigned int vboLength;
    //unsigned int iboLength;

    GLint wheel;
    GLfloat counter;
    GLfloat moveX;
    GLfloat moveY;
    GLfloat moveZ;
    GLfloat rotationAngleX;
    GLfloat rotationAngleY;
    GLfloat rotationAngleZ;

    //GLfloat *vboData;
    //GLuint *indexData;

    //Planet p;
    // std::stack<Planet> planets;

    //QOpenGLBuffer vbo, ibo;
    //QOpenGLShaderProgram shaderProgram;
    //QOpenGLTexture *qTex;

    // p*v*m Reihenfolge ist wichtig!!!
    QMatrix4x4 projektionMatrix;
    QMatrix4x4 viewMatrix;              // --- die Welt (Kamera)
    QMatrix4x4 modelMatrix;             // --- Das 3D-Objekt
    //std::stack<QMatrix4x4> matrixStack;

    void initializeComponents();
    //void initializeVBO(std::string object);
    // void addTextureMap(std::string path = "");
    //void draw(Planet planet);
    void initializeDebugLogger();

};

#endif // MYGLWIDGET_H
