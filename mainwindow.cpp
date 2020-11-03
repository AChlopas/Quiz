#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTime>
#include <QTimer>
#include <QtWidgets>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir("I:/kav11/SQL/MSSQL14.MSSQLSERVER/MSSQL");
    if (!dir.exists()){
        qWarning("Cannot find the directory");
}

    /*QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");{
    QString servername = "127.0.0.1";
    QString dbname = "quiz";
    QString dbpassword = "prog000!";
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setConnectOptions();
    //QString dsn = QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;PASSWORD=%3; Trusted_Connection=YES;").arg(servername).arg(dbname).arg(dbpassword);
    qDebug() << QSqlDatabase::drivers();*/

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");{
        QString servername = "C1";
        QString dbname = "master";
        QString dbpassword = "prog000!";
        db.setConnectOptions();
        QString conn = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;PASSWORD=%3").arg(servername).arg(dbname).arg(dbpassword);
        //QString dsn = QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;PASSWORD=%3; Trusted_Connection=YES;").arg(servername).arg(dbname).arg(dbpassword);
        //qDebug() << QSqlDatabase::drivers();
        //db.setDatabaseName(dsn);

 /*db = QSqlDatabase::addDatabase("QODBC");{
        db.setHostName("127.0.0.1");
        db.setDatabaseName("master");
        db.setUserName("root");
        db.setPassword ("prog000!");
    db.setConnectOptions();
    //QString dsn = QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;PASSWORD=%3; Trusted_Connection=YES;").arg(servername).arg(dbname).arg(dbpassword);
    qDebug() << QSqlDatabase::drivers();*/

    if (!db.open()){
        QErrorMessage querr(this);
        QSqlError err = db.lastError();
        qDebug() << err.text();
  }
    else{
        QString ameryka;
        QString kura;
        QString jezus;

        QSqlQuery query;
            query.prepare("INSERT INTO tabela (id_quiz, pytanie, data) VALUES (:id_quiz, :pytanie, :data)");
            query.bindValue(":id_quiz", 4);
            query.bindValue(":pytanie", ameryka);
            query.bindValue(":data", 1492);
            query.bindValue(":id_quiz", 1);
            query.bindValue(":pytanie", kura);
            query.bindValue(":data", -1000);
            query.bindValue(":id_quiz", 2);
            query.bindValue(":pytanie", jezus);
            query.bindValue(":data", 0);
            query.exec("SELECT pytanie, data FROM `quiz`.`tabela` ORDER BY RAND() LIMIT 2;");
            //query.exec("SELECT id_quiz, pytanie, data FROM tabela");
            if(!query.exec()) {
            QErrorMessage qerr(this);
            QSqlError err = query.lastError();
            qDebug() << err.text();
         }
            else {
                qDebug() << "YAAAAAAAAS";
            }
    }
    }

   //Deklaracja danych
    uint idlewy = 0;
    uint idprawy = 0;
    QString pytanielewy = "Wylosuj pytanie";
    QString pytanieprawy = "Losuj!";
    int datalewy = 0;
    int dataprawy = 0;

    QSqlQuery query;
    //Dane do lewego i prawego przycisku:
    if (query.isSelect())
    {
        //pierwszy zestaw danych
        query.first();
         idlewy = query.value(0).toInt();
         pytanielewy = query.value(1).toString();
         datalewy = query.value(2).toInt();

        //drugi zestaw danych
        query.last();
         idprawy = query.value(0).toInt();
         pytanieprawy = query.value(1).toString();
         dataprawy = query.value(2).toInt();
    }
    else
    {
        qDebug() << "no nie da się";
    }

    //obsługa przycisków:
    /*obsługa buttona
    za tekst buttona lewy przypinam zmianną pytanielewy
    za tekst buttona prawy przypinam zmianną pytanieprawy

    po przyciśnięciu buttonlewy->
    sprawdzam czy datalewy<dataprawy
        Tak? +1 punkt
        Nie? GAMEOVER!

    po przyciśnięciu buttonprawy->
    sprawdzam czy dataprawy<datalewy
        Tak? +1 punkt
        Nie? GAMEOVER!

    //obsługa rysunków: //czyli pobieramy ścieżkę i dynamicznie tylko zmieniamy nazwę rysunku - nazwa rysunku odpowiada ID danego pytania tj. pytanie o ID 1 ma rysunek o nazwie 1 i rozszerzeniu.png
    QPixmap rysuneklewy("TWOJASCIEZKA[idlewy].png");
    QPixmap rysunekprawy("TWOJASCIEZKA[idprawy].png");*/
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_prawywybor_clicked()
{

    int datalewy;
    int dataprawy;
    int n = 0;
    QString pytanieprawy;

    if (datalewy<dataprawy){
        ui->points->display(n+1);
        ui->lewywybor->setText(pytanieprawy);
    }
    else {
        ui->prawywybor->setEnabled(false);
        ui->lewywybor->setEnabled(false);
        qDebug() << "przegrana!";
    }
  //setConnection();
  QSqlQuery query;
   //query.exec("SELECT pytanie, data FROM `quiz`.`tabela` ORDER BY RAND() LIMIT 2;");
  /* if(query.exec("SELECT pytanie, data FROM tabela ORDER BY RAND() LIMIT 2")) {
   qDebug() << ("OK!");

   while (query.next())
   {
   uint id = query.value(0).toInt();
   QString pytanie = query.value(1).toString();
   int data = query.value(2).toInt();
   qDebug() << id << pytanie << data;
   }
   }
   else {
   QErrorMessage qerr(this);
   QSqlError err = query.lastError();
   qDebug() << err.text();
}*/
   //qDebug() << "WYGRALES!";

    }

void MainWindow::on_lewywybor_pressed()
{
   //ui->prawywybor->setEnabled(false);
   //ui->lewywybor->setEnabled(false);
   qDebug() << "przegrana!";
   //int n=0;
    //ui->points->display(n+1);
}
