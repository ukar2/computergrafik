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
    QObject::connect(ui->openGLWidget, SIGNAL(wheelValueForZChanged(int)), ui->spbZoom, SLOT(setValue(int)));
    QObject::connect(ui->chkRotate, SIGNAL(clicked(bool)), ui->openGLWidget, SLOT(setChkBoxFlag(bool)));
    QObject::connect(ui->chkRotate, SIGNAL(clicked(bool)), ui->hrlSliderRotateY, SLOT(setDisabled(bool)));
}


MainWindow::~MainWindow()
{
    delete ui;
}



