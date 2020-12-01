#include "mythread.h"
#include "myserwer.h"
//#include "ui_mythread.h"

Mythread::Mythread(int id, QObject *parent)
        : QThread(parent)
        //, ui(new Ui::Mythread)
{

    this -> socketDescriptor = id;

//    lineEdit = new QLineEdit;

//    logBtn = new QPushButton("loguj");
//    connect(logBtn,SIGNAL(clicked()),this,SLOT(newConnect()));

//    QHBoxLayout *bottomlayout = new QHBoxLayout;
//    bottomlayout->addWidget(logBtn);
//    bottomlayout-> addWidget (lineEdit);
//    setLayout(bottomlayout);

}



void Mythread::run()
{
   qDebug() << "Starting thread" ;
   socket = new QTcpSocket();
   if(!socket->setSocketDescriptor(this->socketDescriptor))
   {
       emit error (socket ->error());
       return;
   }
   connect(socket, SIGNAL(readyRead()), this, SLOT (readyRed()));
   connect(socket, SIGNAL(disconnected()), this, SLOT (disconnected()));
   qDebug() << socketDescriptor << "Client connected";

   exec();
}

void Mythread::readyRead()
{
   QByteArray data = socket->readAll();
   qDebug() << socketDescriptor << "NICK: " << data;
   socket -> write(data);
}

void Mythread::disconnected()
{
    qDebug() << socketDescriptor << "disconnected";
    socket -> deleteLater();
    exit(0);
}
