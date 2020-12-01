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



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //nowe
    MainWindow(quint16 t_port);
    quint16 port() const;


    const quint16 CLIENTS = 2;

    QString idToString(int t_id) const;
        int idFromString(const QString &t_message) const;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer *timer;

    QSqlDatabase db;
    void do_stuff();
    int idlewy;
    int idprawy;
    QString pytanielewy = "Wylosuj";
    QString pytanieprawy = "Pytanie";
    int datalewy = 1;
    int dataprawy = 0;

    int n = -1;
    int czas = 3000;

//    QPushButton *zapis;
//    QTextEdit *tedit;
//    QHBoxLayout *hbl;
//    QPushButton *loadButton;
//    QPushButton *saveButton;
//    QString *contacts;
    //QString nick;


    //~logowanie();
    QTextEdit *layoutnick;
    QByteArray nick;
    //QTextEdit *layoutnick;
    QTcpSocket *_pSocket;


    bool state=false;
        QString IP,Port,Message;
        QString time;
        int ClientNumber;

//nowe
public slots:
    void newClient(int t_id);
    void process(const QString &t_message) const;
    void setId(int t_id);

private slots:
    void on_pushButton_create_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_prawywybor_clicked();

    void on_lewywybor_pressed();

    //void nickLayout();

//nowe
signals:
    void passClientNum(QString IP,QString Port,int ClientNum,QString Message,bool state,QString time);
    void allClientsConnected();
    void allClientsNotConnected();
    void connectionError(const QString &t_message) const;
    void connected() const;


private:
        //ClientUI *clientui;
    Ui::MainWindow *ui;
    quint16 m_connectedClients = 0;
    bool m_allClientsConnected = false;
    MainWindow *m_serverNetwork;
    MainWindow *m_clientNetwork;
    int m_id = -1;
};

#endif // MAINWINDOW_H
