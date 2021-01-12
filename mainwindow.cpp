#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    timerOkno();

    QString path = "I:/SQLiteStudio/bazaqt";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+".db");

    if (!db.open()){
        qDebug() << "nieee";
  }

}

void MainWindow::timerOkno()
{
        timer = new QTimer(this);
        timer->setInterval(30000);
        connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
        timer -> start();
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


void MainWindow::sendMessage()
{
    pt = n;

    QString string = lineEdit->text();
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<userstr;
    out<<string;
    out<<pt;
    m_tcpsocket->write(block);
    lineEdit->clear();


    QSqlQuery query(db);
    query.prepare("INSERT INTO uczestnicy (pt, imie) VALUES(?, ?);");
    query.addBindValue(pt);
    query.addBindValue(string);
    query.exec();

query.exec("SELECT * FROM uczestnicy;");

while (query.next()){
    pt = query.value(n).toInt();
    string = query.value(userstr).toString();
}

}


void MainWindow::MySlot()
{
    qDebug() << "Timer...";
    msgBox.setText("czas się skończył");
    if (msgBox.exec()){
        ui->prawywybor->setEnabled(false);
        ui->lewywybor->setEnabled(false);
    }
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
