#ifndef PROBANAC_H
#define PROBANAC_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class probanaCData;

class probanaC
{
    Q_OBJECT
public:
    probanaC();
    probanaC(const probanaC &);
    probanaC &operator=(const probanaC &);
    ~probanaC();

private:
    QSharedDataPointer<probanaCData> data;
};

#endif // PROBANAC_H
