#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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
    bool czasminal;

private slots:

    void on_prawywybor_clicked();

    void on_lewywybor_pressed();

private:
    Ui::MainWindow *ui;
    //QSqlDatabase db;

};

#endif // MAINWINDOW_H
