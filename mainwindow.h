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
#include <QTextEdit>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QPlainTextEdit>



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

    QPushButton *zapis;
    QTextEdit *tedit;
    QHBoxLayout *hbl;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QString *contacts;
    QString nick;

private slots:

    void on_prawywybor_clicked();

    void on_lewywybor_pressed();

    void saveToFile();

private:
    Ui::MainWindow *ui;
    //QSqlDatabase db;

};

#endif // MAINWINDOW_H
