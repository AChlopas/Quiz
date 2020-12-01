#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytimer.h"
#include "mythread.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtWidgets>
#include <QDir>
#include <QPixmap>
#include <QDataStream>
#include <QTcpSocket>
#include <QSocketDescriptor>
#include <QSocketNotifier>


//void MainWindow::newClient(int t_id)
//{
//    qDebug() << "ServerGame::newClient";
//    ++m_connectedClients;

////    m_serverNetwork->sendOne(t_id, m_parser.idToString(t_id));
////    m_serverNetwork->sendAll(m_parser.snakesToString(m_snakes));

//    if (t_id == CLIENTS - 1) {
//        m_allClientsConnected = true;
//        emit allClientsConnected();
//    }

//}

//quint16 MainWindow::port() const
//{
//    return m_serverNetwork->port();
//}

//void MainWindow::setId(int t_id)
//{
//    qDebug() << "ClientGame::setId" << t_id;
//    m_id = t_id;
//}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QDir dir("I:/SQLiteStudio");
    if (!dir.exists()){
        qWarning("Cannot find the directory");
}

    QString path = "I:/SQLiteStudio/bazaqt";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+"db");

    if (!db.open()){
        qDebug() << "nieee";
  }

        QSqlQuery query(db);
       query.prepare("CREATE TABLE IF NOT EXISTS quiz(id  INT PRIMARY KEY, "
                     "kategoria STRING (40),"
                     "pytanie   STRING (40),"
                     "data      INT);");
        if(!query.exec()) {
        QErrorMessage qerr(this);
        QSqlError err = query.lastError();
        qDebug() << err.text();
     }
        else{
            //query.exec("DELETE FROM quiz");
            query.prepare("INSERT INTO quiz (id, pytanie, data, kategoria) VALUES(:id, :pytanie, :data, :kategoria);");
            query.bindValue(":id", 5);
            query.bindValue(":pytanie", "JEZUS");
            query.bindValue(":data", 0);
            query.bindValue(":kategoria", "5");
            query.exec();
            query.bindValue(":id", 4);
            query.bindValue(":pytanie", "RADYJKO");
            query.bindValue(":data", 1894);
            query.bindValue(":kategoria","4");
            query.exec();
            query.bindValue(":id", 3);
            query.bindValue(":pytanie", "ODKRYCIE AMERYKI");
            query.bindValue(":data", 1492);
            query.bindValue(":kategoria", "3");
            query.exec();
            query.bindValue(":id", 2);
            query.bindValue(":pytanie", "KURA");
            query.bindValue(":data", -1000);
            query.bindValue(":kategoria", "2");
            query.exec();
            query.bindValue(":id", 1);
            query.bindValue(":pytanie", "SLONCE");
            query.bindValue(":data", -800000);
            query.bindValue(":kategoria", "1");
            query.exec();
            query.bindValue(":id", 6);
            query.bindValue(":pytanie", "VELOCIRAPTOR");
            query.bindValue(":data", -700000);
            query.bindValue(":kategoria", "6");
            query.exec();

            if(!query.exec()) {
            QErrorMessage qerr(this);
            QSqlError err = query.lastError();
            qDebug() << err.text();
         }
       }
}

MyTimer::MyTimer()
{
    timer = new QTimer(this);
    timer->setInterval(30000);
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
    timer -> start();
}

void MyTimer::MySlot()
{
    qDebug() << "Timer...";
    QMessageBox msgBox;
    msgBox.setText("czas się skończył");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_prawywybor_clicked()
{            
    if (datalewy>dataprawy){
        n = n+1;
        ui->points->display(n);

  QSqlQuery query;
   query.exec("SELECT id, pytanie, data, kategoria FROM quiz ORDER BY RANDOM() LIMIT 2;");

   while (query.next())
   {
       QString rysunekL= "lowa";
               QString rysunekP = "proba";
              //pierwszy zestaw danych
              query.first();
              idlewy = query.value(0).toInt();
              ui -> lewywybor -> setText(query.value(1).toString());
              datalewy = query.value(2).toInt();
              rysunekL = query.value(3).toString();
              QString sciezkabaza = "C:/Users/ana/Desktop/WEMIF-kursy 2 rok/prog. apli/quizz/grafiki/";
              QString rozszerzenie = ".jpg";
              QPixmap sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
              QPixmap sciezkaP = sciezkabaza + rysunekP+rozszerzenie;

               ui->rysunekLew->setPixmap(sciezkaL);
               ui->rysunekPraw->setPixmap(sciezkaP);

              //drugi zestaw danych
               query.last();
                idprawy = query.value(0).toInt();
                ui ->prawywybor -> setText(query.value(1).toString());
                dataprawy = query.value(2).toInt();
                rysunekP = query.value(3).toString();
                sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
                sciezkaP = sciezkabaza + rysunekP+rozszerzenie;
                ui->rysunekLew->setPixmap(sciezkaL);
                ui->rysunekPraw->setPixmap(sciezkaP);
          }
           }
           else {
                ui->prawywybor->setEnabled(false);
                ui->lewywybor->setEnabled(false);
                qDebug() << "przegrana!";
                //saveToFile();
       }

    }

void MainWindow::on_lewywybor_pressed()
{
    if (dataprawy>datalewy){
        n = n+1;
        ui->points->display(n);

    QSqlQuery query;
     query.exec("SELECT id, pytanie, data, kategoria FROM quiz ORDER BY RANDOM() LIMIT 2;");
     while (query.next())
     {
             QString rysunekL= "lowa";
                     QString rysunekP = "proba";
                    //pierwszy zestaw danych
                    query.first();
                     idlewy = query.value(0).toInt();
                     ui ->lewywybor -> setText(query.value(1).toString());
                     datalewy = query.value(2).toInt();
                     rysunekL = query.value(3).toString();
                     QString sciezkabaza = "C:/Users/ana/Desktop/WEMIF-kursy 2 rok/prog. apli/quizz/grafiki/";
                     QString rozszerzenie = ".jpg";
                     QPixmap sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
                     QPixmap sciezkaP = sciezkabaza + rysunekP+rozszerzenie;

                     ui->rysunekLew->setPixmap(sciezkaL);
                     ui->rysunekPraw->setPixmap(sciezkaP);

                    //drugi zestaw danych
                     query.last();
                      idprawy = query.value(0).toInt();
                      ui ->prawywybor -> setText(query.value(1).toString());
                      dataprawy = query.value(2).toInt();
                      rysunekP = query.value(3).toString();
                      sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
                      sciezkaP = sciezkabaza + rysunekP+rozszerzenie;
                      ui->rysunekLew->setPixmap(sciezkaL);
                      ui->rysunekPraw->setPixmap(sciezkaP);
                }
                 }
                 else {
                      ui->prawywybor->setEnabled(false);
                      ui->lewywybor->setEnabled(false);
                      qDebug() << "przegrana!";
                      //saveToFile();
             }
}



