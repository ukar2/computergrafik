#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->hrlSliderRotateX, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(receiveRotationX(int)));
    QObject::connect(ui->hrlSliderRotateY, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(receiveRotationY(int)));
    QObject::connect(ui->hrlSliderRotateZ, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(receiveRotationZ(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
