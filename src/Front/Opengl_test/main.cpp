#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    setlocale(LC_NUMERIC, "C");





    MainWindow w;
    w.show();
//    glView g;
//    g.show();

    return app.exec();
}
