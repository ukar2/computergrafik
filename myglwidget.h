#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>

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
};

#endif // MYGLWIDGET_H
