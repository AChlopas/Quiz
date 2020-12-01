#ifndef MYSERWER_H
#define MYSERWER_H

#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include "mythread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void StartServer();

    QTcpServer *m_tcpserver;
    QPushButton *startBtn;
    QWidget *window;

private slots:
   // void newConnect();
   // void incomingConnection (qintptr socketDescriptor);

protected:
   // Ui::MyServer *ui;
    void incomingConnection (qintptr socketDescriptor);
};

#endif // MYSERWER_H
