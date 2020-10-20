#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTime>
#include <QTimer>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
        qApp->quit();
}

void MainWindow::on_prawywybor_clicked()
{
//#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
   ui->prawywybor->setEnabled(false);
   ui->lewywybor->setEnabled(false);
    qDebug() << "przegrales!";
 //#endif

}

void MainWindow::on_lewywybor_pressed()
{
//#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
   ui->prawywybor->setEnabled(false);
    qDebug() << "wygrales!";
 //#endif
   int n=0;
    ui->points->display(n+1);
}

