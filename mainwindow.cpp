#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytimer.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtWidgets>
#include <QDir>
#include <QPixmap>
#include <QDataStream>

void MainWindow::saveToFile(){

    auto central = new QWidget;
        central->setLayout(hbl);

        setCentralWidget(central);

    QString Nplik = "C:/Users/ana/Desktop/WEMIF-kursy 2 rok/prog. apli/quizz/WYNIKI.txt";
    QFile plik(Nplik);
    if(plik.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
          {


              QTextStream stream(&plik);
              nick = tedit->toPlainText();

              stream << "nick: " << nick << "\n";
              stream << "wynik: " << n << "\n";

    }
    plik.close();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle ("NICK");
    zapis = new QPushButton;
    tedit = new QTextEdit;
    hbl = new QHBoxLayout;
    QObject::connect(zapis, SIGNAL(clicked()), this, SLOT(saveToFile()));
    zapis -> setText("ZAPISZ");
    hbl->addWidget(tedit);
    hbl->addWidget(zapis);

    //setLayout(hbl);

    QDir dir("I:/SQLiteStudio");
    if (!dir.exists()){
        qWarning("Cannot find the directory");
}

    QString path = "I:/SQLiteStudio/bazaqt";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path+"db");

    if (!db.open()){
        qDebug() << "nieee";
  }

        QSqlQuery query(db);
       query.prepare("CREATE TABLE IF NOT EXISTS quiz(id  INT PRIMARY KEY, "
                     "kategoria STRING (40),"
                     "pytanie   STRING (40),"
                     "data      INT);");
        if(!query.exec()) {
        QErrorMessage qerr(this);
        QSqlError err = query.lastError();
        qDebug() << err.text();
     }
        else{
            //query.exec("DELETE FROM quiz");
            query.prepare("INSERT INTO quiz (id, pytanie, data, kategoria) VALUES(:id, :pytanie, :data, :kategoria);");
            query.bindValue(":id", 5);
            query.bindValue(":pytanie", "JEZUS");
            query.bindValue(":data", 0);
            query.bindValue(":kategoria", "5");
            query.exec();
            query.bindValue(":id", 4);
            query.bindValue(":pytanie", "RADYJKO");
            query.bindValue(":data", 1894);
            query.bindValue(":kategoria","4");
            query.exec();
            query.bindValue(":id", 3);
            query.bindValue(":pytanie", "ODKRYCIE AMERYKI");
            query.bindValue(":data", 1492);
            query.bindValue(":kategoria", "3");
            query.exec();
            query.bindValue(":id", 2);
            query.bindValue(":pytanie", "KURA");
            query.bindValue(":data", -1000);
            query.bindValue(":kategoria", "2");
            query.exec();
            query.bindValue(":id", 1);
            query.bindValue(":pytanie", "SLONCE");
            query.bindValue(":data", -800000);
            query.bindValue(":kategoria", "1");
            query.exec();
            query.bindValue(":id", 6);
            query.bindValue(":pytanie", "VELOCIRAPTOR");
            query.bindValue(":data", -700000);
            query.bindValue(":kategoria", "6");
            query.exec();

            if(!query.exec()) {
            QErrorMessage qerr(this);
            QSqlError err = query.lastError();
            qDebug() << err.text();
         }
       }
}

MyTimer::MyTimer()
{
    timer = new QTimer(this);
    timer->setInterval(30000);
    connect(timer, SIGNAL(timeout()), this, SLOT(MySlot()));
    timer -> start();
}

void MyTimer::MySlot()
{
    qDebug() << "Timer...";
    QMessageBox msgBox;
    msgBox.setText("czas się skończył");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_prawywybor_clicked()
{            
    if (datalewy>dataprawy){
        n = n+1;
        ui->points->display(n);

  QSqlQuery query;
   query.exec("SELECT id, pytanie, data, kategoria FROM quiz ORDER BY RANDOM() LIMIT 2;");

   while (query.next())
   {
       QString rysunekL= "lowa";
               QString rysunekP = "proba";
              //pierwszy zestaw danych
              query.first();
              idlewy = query.value(0).toInt();
              ui -> lewywybor -> setText(query.value(1).toString());
              datalewy = query.value(2).toInt();
              rysunekL = query.value(3).toString();
              QString sciezkabaza = "C:/Users/ana/Desktop/WEMIF-kursy 2 rok/prog. apli/quizz/grafiki/";
              QString rozszerzenie = ".jpg";
              QPixmap sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
              QPixmap sciezkaP = sciezkabaza + rysunekP+rozszerzenie;

               ui->rysunekLew->setPixmap(sciezkaL);
               ui->rysunekPraw->setPixmap(sciezkaP);

              //drugi zestaw danych
               query.last();
                idprawy = query.value(0).toInt();
                ui ->prawywybor -> setText(query.value(1).toString());
                dataprawy = query.value(2).toInt();
                rysunekP = query.value(3).toString();
                sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
                sciezkaP = sciezkabaza + rysunekP+rozszerzenie;
                ui->rysunekLew->setPixmap(sciezkaL);
                ui->rysunekPraw->setPixmap(sciezkaP);
          }
           }
           else {
                ui->prawywybor->setEnabled(false);
                ui->lewywybor->setEnabled(false);
                qDebug() << "przegrana!";
                saveToFile();
       }

    }

void MainWindow::on_lewywybor_pressed()
{
    if (dataprawy>datalewy){
        n = n+1;
        ui->points->display(n);

    QSqlQuery query;
     query.exec("SELECT id, pytanie, data, kategoria FROM quiz ORDER BY RANDOM() LIMIT 2;");
     while (query.next())
     {
             QString rysunekL= "lowa";
                     QString rysunekP = "proba";
                    //pierwszy zestaw danych
                    query.first();
                     idlewy = query.value(0).toInt();
                     ui ->lewywybor -> setText(query.value(1).toString());
                     datalewy = query.value(2).toInt();
                     rysunekL = query.value(3).toString();
                     QString sciezkabaza = "C:/Users/ana/Desktop/WEMIF-kursy 2 rok/prog. apli/quizz/grafiki/";
                     QString rozszerzenie = ".jpg";
                     QPixmap sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
                     QPixmap sciezkaP = sciezkabaza + rysunekP+rozszerzenie;

                     ui->rysunekLew->setPixmap(sciezkaL);
                     ui->rysunekPraw->setPixmap(sciezkaP);

                    //drugi zestaw danych
                     query.last();
                      idprawy = query.value(0).toInt();
                      ui ->prawywybor -> setText(query.value(1).toString());
                      dataprawy = query.value(2).toInt();
                      rysunekP = query.value(3).toString();
                      sciezkaL = sciezkabaza + rysunekL+rozszerzenie;
                      sciezkaP = sciezkabaza + rysunekP+rozszerzenie;
                      ui->rysunekLew->setPixmap(sciezkaL);
                      ui->rysunekPraw->setPixmap(sciezkaP);
                }
                 }
                 else {
                      ui->prawywybor->setEnabled(false);
                      ui->lewywybor->setEnabled(false);
                      qDebug() << "przegrana!";
                      saveToFile();
             }
}


//zapisz::zapisz (QWidget *parent):QDialog(parent){
//    setWindowTitle ("NICK");
//    //combo = new QComboBox;
//    //loadButton= new QPushButton;
//    //saveButton = new QPushButton;
//    pushbutton = new QPushButton;
//    tedit = new QTextEdit;
//    hbl = new QHBoxLayout;
//    QObject::connect(pushbutton, SIGNAL(clicked()), this, SLOT(saveToFile()));
//    //QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
//    //QObject::connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
//    pushbutton -> setText("ZAPISZ");
//    //saveButton -> setText("2 proba");

//    hbl->addWidget(tedit);
//    hbl->addWidget(pushbutton);
//    hbl->addWidget(saveButton);
//    hbl->addWidget(loadButton);
//    setLayout(hbl);

//}

//void Character::read(const QJsonObject &json)
//{
//    if (json.contains("name") && json["name"].isString())
//        mName = json["name"].toString();
//}

//void Character::write(QJsonObject &json) const
//{
//    json["name"] = mName;
//}

//bool Game::saveGame(Game::SaveFormat saveFormat) const
//{
//    QFile saveFile(saveFormat == Json
//        ? QStringLiteral("save.json")
//        : QStringLiteral("save.dat"));

//    if (!saveFile.open(QIODevice::WriteOnly)) {
//        qWarning("Couldn't open save file.");
//        return false;
//    }

//    QJsonObject gameObject;
//    write(gameObject);
//    saveFile.write(saveFormat == Json
//        ? QJsonDocument(gameObject).toJson()
//        : QCborValue::fromJsonValue(gameObject).toCbor());

//    return true;
//}


