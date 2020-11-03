#include "mainwindow.h"
#include "mainwindow.cpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //QApplication app(argc, argv);
      //  if (!setConnection()){
     //       return 1;}
}

