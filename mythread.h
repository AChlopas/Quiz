#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtGui>
#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>


#include <QMutex>
#include <QWaitCondition>
#include <QSocketDescriptor>
#include <QSocketNotifier>


QT_BEGIN_NAMESPACE
namespace Ui { class Mythread; }
QT_END_NAMESPACE

class Mythread : public QThread
{
    Q_OBJECT
public:
   explicit Mythread(int id, QObject *parent = 0);
    void run ();
    QLineEdit *lineEdit;
    QPushButton *logBtn;
    QPushButton *connectBtn;
    QHBoxLayout *bottomlayout;

signals:
void error (QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    Ui::Mythread *ui;
    QTcpSocket *socket;
    int socketDescriptor;
};

#endif // MYTHREAD_H
