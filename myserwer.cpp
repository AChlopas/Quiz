#include "myserwer.h"
#include "mythread.h"

MyServer::MyServer(QObject *parent)
    :QTcpServer(parent)
{
    window = new QWidget;
    startBtn = new QPushButton("start");
    connect(startBtn,SIGNAL(clicked()),this,SLOT(incomingConnection()));
    QHBoxLayout *bottomlayout = new QHBoxLayout;
    bottomlayout->addWidget(startBtn);
     window->setLayout(bottomlayout);
}

void MyServer::StartServer()
{
    m_tcpserver = new QTcpServer;
    if (!m_tcpserver->listen(QHostAddress::LocalHost))
    {
        qDebug() << "Server do not start";
    }
    else {
        qDebug() << "Listening...";
        window->show();

    }
}


void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << "Conecting...";
    Mythread *thread = new Mythread(socketDescriptor, m_tcpserver);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
