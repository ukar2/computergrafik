#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat frmt;
    frmt.setVersion(4,5);
    frmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    frmt.setOption(QSurfaceFormat::DeprecatedFunctions);
    frmt.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(frmt);

    QApplication app(argc, argv);
    MainWindow w;

    w.show();

    return app.exec();
}
