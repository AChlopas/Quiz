#include "mainwindow.h"
#include "mainwindow.cpp"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCoreApplication>
#include <QMainWindow>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    return a.exec();

}

