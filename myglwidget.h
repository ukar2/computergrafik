#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QWidget>

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

private:
    GLfloat moveX;
    GLfloat moveY;
    GLfloat moveZ;
};

#endif // MYGLWIDGET_H
