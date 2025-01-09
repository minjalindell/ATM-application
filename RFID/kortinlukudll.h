#ifndef KORTINLUKUDLL_H
#define KORTINLUKUDLL_H
#include <QObject>
#include "QtSerialPort/qserialport.h"
#include "kortinlukudll_global.h"
#include <QSerialPort>

class KORTINLUKUDLL_EXPORT Kortinlukudll: public QObject
{
    Q_OBJECT
public:
    Kortinlukudll(QObject *parent=nullptr);
    ~Kortinlukudll();

    void openSerialPort();
    QString cardNumber;
    QSerialPort* serialPort;
    QString checkCorrectPort();

public slots:
    void readData();

signals:
    void sendNumber(QString);

};

#endif // KORTINLUKUDLL_H
