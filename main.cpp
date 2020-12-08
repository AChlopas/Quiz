#include "mainwindow.h"
#include "serwer.h"
#include "mainwindow.cpp"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


   //QCoreApplication a(argc, argv);
    MyTimer timer;
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    serwer s(nullptr,&w);
    s.show();

    //QObject::connect(startBtn,SIGNAL(clicked()),this,SLOT(MainWidow::noweOkno()));

//    QApplication app(argc, argv);
//    //QTimer::singleShot(6000, &app, SLOT(closed()));
//    //QTimer::singleShot(33000, &QApplication::quit);

    return a.exec();

}

