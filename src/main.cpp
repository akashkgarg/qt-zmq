#include <iostream>
#include <QApplication>
#include <QFileInfo>
#include <QDebug>
#include "mainwindow.h"

//------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    a.exec();
}
