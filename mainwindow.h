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
#include <QTableView>
#include <QSqlTableModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_prawywybor_clicked();

    void on_lewywybor_pressed();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    /*bool setConnection(){

        QDir dir("C:/Users/ana/Desktop/WEMIF-kursy 2 rok/prog. apli/baza danych SQL");
        if (!dir.exists()){
            qWarning("Cannot find the directory");
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString servername = "127.0.0.1";
    QString dbname = "quiz";
    QString dbpassword = "prog000!";
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setConnectOptions();
    QString dsn = QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;PASSWORD=%3; Trusted_Connection=YES;").arg(servername).arg(dbname).arg(dbpassword);
    qDebug() << QSqlDatabase::drivers();

    if (!db.open()){
        qDebug() << ("nooo");
        return false;
  }
    else{
        QString ameryka;
        QString kura;
        QString jezus;

        QSqlQuery query;
            query.prepare("INSERT INTO `quiz`.`tabela` (id_quiz, pytanie, data) VALUES (:id_quiz, :pytanie, :data);");
            query.bindValue(":id_quiz", 4);
            query.bindValue(":pytanie", ameryka);
            query.bindValue(":data", 1492);
            query.bindValue(":id_quiz", 1);
            query.bindValue(":pytanie", kura);
            query.bindValue(":data", -1000);
            query.bindValue(":id_quiz", 2);
            query.bindValue(":pytanie", jezus);
            query.bindValue(":data", 0);
            query.exec("SELECT pytanie, data FROM `quiz`.`tabela` ORDER BY RAND() LIMIT 2;");
            if(!query.exec()) {
            //QErrorMessage qerr(this);
            QSqlError err = query.lastError();
            qDebug() << err.text();
         }
            else {
                qDebug() << "YAAAAAAAAS";
            }
    }

    return true;
}*/
};

#endif // MAINWINDOW_H
