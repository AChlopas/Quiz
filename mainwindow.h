#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QtNetwork>
#include <QtSql>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QLibrary>
#include <QSqlError>
#include <QDir>
#include <QTimeEdit>
#include <QTime>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QPlainTextEdit>
#include <QTcpSocket>
#include <QtNetwork>
#include <QtCore>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    QTimer *timer;
    QMessageBox msgBox;

    QTextEdit *layoutnick;
    QByteArray nick;

    QTcpSocket *_pSocket;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase db;
    int idlewy;
    int idprawy;
    QString pytanielewy = "Wylosuj";
    QString pytanieprawy = "Pytanie";
    int datalewy = 1;
    int dataprawy = 0;

    int n = -1;
    int czas = 3000;

    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *sendBtn;
    QPushButton *connectBtn;
    QTcpSocket *m_tcpsocket;
    QString userstr;

    QWidget *windos = new QWidget;
    void noweOkno();
    void timerOkno();
    int  pt;


private slots:

        void connectTcpServer();
        void connectedServer();
        void sendMessage();

    void on_prawywybor_clicked();

    void on_lewywybor_pressed();

signals:

    void connectionError(const QString &t_message) const;
    void connected() const;

public slots:
    void MySlot();


private:   
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
