#include "kortinlukudll.h"
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QRegularExpression>




Kortinlukudll::Kortinlukudll(QObject *parent): QObject(parent)
{
    qDebug()<<"dll luotu";
    serialPort = new QSerialPort(this);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(readData()));
}

Kortinlukudll::~Kortinlukudll()
{
    serialPort->close();
}

void Kortinlukudll::openSerialPort()
{


    QString port = checkCorrectPort();
    serialPort->setPortName(port);
    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port" << port << "opened successfully.";

    } else {
        qDebug() << "Failed to open serial port" << port << ":" << serialPort->errorString();
    }
}




QString Kortinlukudll::checkCorrectPort()
{
    QString port="";
    QString correct="OL56DEB005B8E7C";

    foreach(const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        qDebug()<<portInfo.serialNumber();
        qDebug()<<portInfo.portName();
        if(portInfo.serialNumber() == correct){
            port = portInfo.portName();
        }
    }

    return port;

}



void Kortinlukudll::readData()
{


    cardNumber = serialPort->readAll();

    cardNumber = cardNumber.mid(3,10);
    QRegularExpression re("\\D+");
    cardNumber = cardNumber.remove(re);

    emit sendNumber(cardNumber);
    qDebug()<<"Dataread";
    qDebug()<<cardNumber;

}

