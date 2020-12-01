#include "mytimer.h"
#include "mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QWidget>
#include <QPushButton>
MyTimer::MyTimer()
{
    timer = new QTimer(this);
    timer->setInterval( 5000 );
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
    timer -> start();    

}

void MyTimer::MySlot()
{
//    qDebug() << "Timer...";
//    QMessageBox msgBox;
//    msgBox.setText("czas się skończył");
//    msgBox.exec();
//         do{
//          // msgBox.set;
//         } while (msgBox.exec());

    }
