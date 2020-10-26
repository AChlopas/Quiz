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

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString servername = "127.0.0.1";
    QString dbname = "quiz.quiz";
    QString dbpassword = "prog000!";
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setConnectOptions();
    QString dsn = QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;PASSWORD=%3; Trusted_Connection=YES;").arg(servername).arg(dbname).arg(dbpassword);
    db.setDatabaseName(dsn);

    if(!db.open())
        {
            qDebug() << "Can't Connect to DB !";
        }
        else
        {
            qDebug() << "Connected Successfully to DB !";


}

   /* //globalne dane
    int data1 =0; //te
    int data2 =0; //te
    int n = 0;

    if (data1==data2)
    {
                QMessageBox::information(this, "losuj!", "to samo" + db.lastError().text());
                db.close();

        //wywolaj losowanie
    }

        else if (data1<data2)
            {
                       ui->lewywybor->setText("punkt!");
                       ui->points->display(n+1); // punkty
                       //losownie wyw.
    }
                       else {
                       ui->lewywybor->setText("UPA!");}*/

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


   ui->lewywybor->setEnabled(false);
   qDebug() << "WYGRALES!";

    QSqlQuery query;
    query.prepare("QUERY TO BE SENT TO THE DB");

     if(query.exec("SELECT pytanie, data FROM quiz ORDERBYRAND() LIMIT [2]"))
     {
         qDebug() << "Query Executed Successfully!";
     }
     else
     {
         qDebug() << "Can't Execute Query!";
     }

    while (query.next()) {
            QString pytanie = query.value(0).toString();
            int data = query.value(1).toInt();
            qDebug() << pytanie << data;
        }

}

void MainWindow::on_lewywybor_pressed()
{
   ui->prawywybor->setEnabled(false);
   ui->lewywybor->setEnabled(false);
   qDebug() << "przegrana!";
   //int n=0;
    //ui->points->display(n+1);
}

