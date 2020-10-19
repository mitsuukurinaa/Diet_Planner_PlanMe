#include "mainwindow.h"
#include "QTranslator"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
