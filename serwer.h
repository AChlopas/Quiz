#ifndef SERWER_H
#define SERWER_H

#include <QWidget>
#include <QtGui>
#include <qnetwork.h>
#include <QTextEdit>
#include <QLineEdit>
#include <QTcpServer>
#include <QPushButton>
#include <QTcpSocket>
#include "qtcpsocket.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
//#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class serwer; }
QT_END_NAMESPACE

class serwer : public QWidget
{
    Q_OBJECT

public:
    serwer(QWidget *parent = nullptr);
    ~serwer();
        int run();
        void bazaU();

    QSqlDatabase db;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *sendBtn;
    QPushButton *startBtn;
    QTcpSocket *m_tcpsocket;
    QTcpServer *m_tcpserver;

private slots:
    void startTcpServer();
    void newConnect();
    void readMessage();

private:
    Ui::serwer *ui;
};
#endif // SERWER_H
