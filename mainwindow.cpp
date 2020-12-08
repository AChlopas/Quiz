#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytimer.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtWidgets>
#include <QDir>
#include <QPixmap>
#include <QDataStream>
#include <QTcpSocket>
#include <QSocketDescriptor>
#include <QSocketNotifier>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    noweOkno();

    QDir dir("I:/SQLiteStudio");
    if (!dir.exists()){
        qWarning("Cannot find the directory");
    }

    QString path = "I:/SQLiteStudio/bazaqt";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+".db");

    if (!db.open()){
        qDebug() << "nieee";
  }

        QSqlQuery query(db);
       query.prepare("CREATE TABLE IF NOT EXISTS quiz(id  INT PRIMARY KEY, "
                     "kategoria STRING (40),"
                     "pytanie   STRING (40),"
                     "login   STRING (10),"
                     "data      INT);");

        bazaU();
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

void MainWindow::bazaU(){

    QSqlQuery query(db);

    query.prepare("CREATE TABLE IF NOT EXISTS uczestnicy(pt  INT, "
                  "imie STRING(40);");
    query.exec();
}
void MainWindow::nowa_odpowiedz(QString imie){


}


void MainWindow::noweOkno()
{

    userstr = QString(tr(" "));
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    lineEdit = new QLineEdit;

    connectBtn = new QPushButton("connect");
    connect(connectBtn,SIGNAL(clicked()),this,SLOT(connectTcpServer()));
    sendBtn = new QPushButton("loguj");
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendMessage()));

    QHBoxLayout *bottomlayout = new QHBoxLayout;
    bottomlayout->addWidget(connectBtn);
    bottomlayout->addWidget(sendBtn);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addWidget(textEdit);
    mainlayout->addWidget(lineEdit);
    mainlayout->addLayout(bottomlayout);

    windos->setLayout(mainlayout);
    windos->show();

}

void MainWindow::connectTcpServer()
{

m_tcpsocket = new QTcpSocket(this);
m_tcpsocket->abort();
m_tcpsocket->connectToHost(QHostAddress::LocalHost,16666);

connect(m_tcpsocket,SIGNAL(connected()),this,SLOT(connectedServer()));
//connect(m_tcpsocket,SIGNAL(readyRead()),this,SLOT(readMessage()));

 textEdit->append(tr("connect server...")+'\n');
connectBtn->setEnabled(false);
}

void MainWindow::connectedServer()
{
 textEdit->append(tr("Connection server succeeded!")+'\n');
}

//void MainWindow::readMessage()
//{
//QString string;
//QByteArray block = m_tcpsocket->readAll();
//QDataStream in(block);
//in.setVersion(QDataStream::Qt_5_15);
//in>>string;
// textEdit->append(tr("User has a message coming\n message is:")+string+'\n');
//}

void MainWindow::sendMessage()
{

    //QString id=userstr.left(2);
    id = n;
    QString userstr;

    int type;
    type = 1;
    QString string = lineEdit->text();
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<userstr;
    out<<type;
    out<<string;
    out<<id;
    m_tcpsocket->write(block);
    lineEdit->clear();


    QSqlQuery query;
    query.prepare("INSERT INTO uczestnicy (pt, imie) VALUES(:pt, :imie);");
    query.bindValue(":pt", id);
    query.exec();
    query.bindValue(":imie", userstr);
    query.exec();
    if(!query.exec()) {
    QErrorMessage qerr(this);
    QSqlError err = query.lastError();
    qDebug() << err.text();
    }

query.exec("SELECT * FROM uczestnicy LIMIT 1;");

while (query.next()){
    id = query.value(0).toInt() ;
    userstr = query.value(1).toString();
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
                QSqlQuery query;
                query.prepare("INSERT INTO uczestnicy (wynik) VALUES(:n);");
                query.bindValue(":n",n);
                query.exec();
                ui->prawywybor->setEnabled(false);
                ui->lewywybor->setEnabled(false);
                qDebug() << "przegrana!";

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
                        QSqlQuery query;
                      ui->prawywybor->setEnabled(false);
                      ui->lewywybor->setEnabled(false);
                      query.prepare("INSERT INTO uczestnicy (wynik) VALUES(:n);");
                      query.bindValue(":n", n);
                      query.exec();
                      qDebug() << "przegrana!";

             }
}
