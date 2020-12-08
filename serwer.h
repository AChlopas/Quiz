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
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class serwer; }
QT_END_NAMESPACE

class serwer : public QWidget
{
    Q_OBJECT

public:
    serwer(QWidget *parent = nullptr);
    serwer(QWidget *parent = nullptr, MainWindow *mainwindow=nullptr);
    ~serwer();
        int run();

    MainWindow *mainwindow;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *sendBtn;
    QPushButton *startBtn;
    QTcpSocket *m_tcpsocket;
    QTcpServer *m_tcpserver;

private slots:
    void startTcpServer();
   // void sendMessage();
    void newConnect();
    void readMessage();

private:
    Ui::serwer *ui;
};
#endif // SERWER_H
