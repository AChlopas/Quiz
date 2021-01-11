#include "serwer.h"
#include "ui_serwer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QErrorMessage>
#include <QSqlError>
//#include "mainwindow.h"
serwer::serwer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serwer)
{

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

    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    startBtn = new QPushButton("start");
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startTcpServer()));

    QHBoxLayout *bottomlayout = new QHBoxLayout;
    bottomlayout->addWidget(startBtn);
    setLayout(bottomlayout);
    bottomlayout->addWidget(textEdit);
    }

    void serwer::startTcpServer()
    {
    startBtn->setEnabled(false);
    m_tcpserver = new QTcpServer;
    m_tcpserver->listen(QHostAddress::Any,16666);
    connect(m_tcpserver,SIGNAL(newConnection()),this,SLOT(newConnect()));
    }

    void serwer::newConnect()
    {
    m_tcpsocket = m_tcpserver->nextPendingConnection();
    connect(m_tcpsocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    }

    void serwer::readMessage()
    {
    QString userstr;
    int pt;
    QString strpt;
    QString string;
    QByteArray block = m_tcpsocket->readAll();
    QDataStream in(block);

    in.setVersion(QDataStream::Qt_5_15);
    in>>userstr;
    in>>string;
    in>>pt;

    strpt = QString::number(pt);

    textEdit->append( string + tr(" gain number of points: ")+ strpt +'\n');

    }

    void serwer::bazaU(){

         QSqlQuery query(db);

         query.prepare("CREATE TABLE IF NOT EXISTS uczestnicy(pt  INT, "
                       "imie STRING(40);");
         query.exec();
     }


serwer::~serwer()
{
    delete ui;
}

