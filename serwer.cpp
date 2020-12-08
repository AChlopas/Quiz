#include "serwer.h"
#include "ui_serwer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mainwindow.h"
serwer::serwer(QWidget *parent, MainWindow *mainwindow)
    : QWidget(parent)
    , ui(new Ui::serwer)
{
    ui->setupUi(this);
    this->mainwindow=mainwindow;
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);

    //lineEdit = new QLineEdit;

    startBtn = new QPushButton("start");
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startTcpServer()));

    //sendBtn = new QPushButton("sendToLogin");
    //connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendMessage()));
    QHBoxLayout *bottomlayout = new QHBoxLayout;
    bottomlayout->addWidget(startBtn);
    setLayout(bottomlayout);
    bottomlayout->addWidget(textEdit);

//    QVBoxLayout *mainlayout = new QVBoxLayout;
//    mainlayout->addWidget(textEdit);
//    mainlayout->addWidget(lineEdit);
//    mainlayout->addLayout(bottomlayout);
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
    //QString id=userstr.left(2);
    int id;
    int type;
    QString string;
    QByteArray block = m_tcpsocket->readAll();
    QDataStream in(block);

    in.setVersion(QDataStream::Qt_5_15);
    in>>userstr;
    in>>type;
    in>>string;
    in>>id;
    textEdit->append( userstr + tr(" gain number of points: ")+ id +'\n');
    //textEdit->setText(userstr + " uzyskales tyle punktow: " + id);

    }

//    void serwer::sendMessage()
//    {
//    QString string = lineEdit->text();
//    QByteArray block;
//    QDataStream out(&block,QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_15);
//    out<<string;
//    m_tcpsocket->write(block);
//    }

serwer::~serwer()
{
    delete ui;
}

