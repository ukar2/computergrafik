#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QWidget>

class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent);
    ~MyGLWidget();
};

#endif // MYGLWIDGET_H
