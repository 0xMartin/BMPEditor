#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // nacteni theme
    QFile theme(":/Resources/Combinear.qss");
    if(theme.open(QFile::ReadOnly)) {
        qDebug() << "Theme load ... ok";
    } else {
        qDebug() << "Theme load ... fail";
    }
    app.setStyleSheet(theme.readAll());

    // hlavni okno aplikace
    MainWindow w;
    w.show();

    return app.exec();
}
