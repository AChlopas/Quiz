QT       += core gui
QT += core
QT       += core gui sql

QT +=core sql
QT += sql
QT += core
QT += widgets
QT += network
QT       += core gui serialport

TARGET = qtsqltest
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    mytimer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../baza danych SQL/LineInst.exe.mwb \
    ../baza danych SQL/tabela.csv \
    grafiki/1.jpg \
    grafiki/2.jpg \
    grafiki/3.jpg \
    grafiki/4.jpg \
    grafiki/5.jpg \
    grafiki/6.jpg \
    libmysql.dll \
    libmysqld.dll \
    serwer.pro.user

SUBDIRS += \
    serwer.pro
