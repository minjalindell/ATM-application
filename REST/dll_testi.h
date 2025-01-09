#ifndef DLL_TESTI_H
#define DLL_TESTI_H

#include "dll-testi_global.h"
#include <QObject>
#include <QNetworkReply>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSqlQuery>
#include <QSqlDatabase>

class DLLTESTI_EXPORT Dll_testi : public QObject
{
    Q_OBJECT
public:
    Dll_testi(QObject *parent = nullptr);
    void login(QString, QString);
    QJsonObject jsonObj;
    void setWebToken(const QByteArray &newWebToken);
    void saldo();
    QString accountNumber;
    QByteArray currentToken();
    double balance;
    void nosto(double);
    double num;
    void getTransaction();
    void TransActionAdd();
    QJsonArray getJsonArray() const;
    void getName();


private slots:
    void loginSlot(QNetworkReply *reply);
    void saldoSlot(QNetworkReply *reply);
    void nostoSlot(QNetworkReply *reply);
    void TransactionSlot(QNetworkReply *reply);
    void TiliSlot(QNetworkReply *reply);
    void nameSlot(QNetworkReply *reply);
signals:
    void sendResponse(bool);
    void sendBalance(QString, double);
    void transActionsReady();
    void sendName(QString);
    void send_response(QString);

private:
    QByteArray response_data;
    QNetworkReply *reply;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *saldoManager;
    QNetworkAccessManager *nostoManager;
    QNetworkAccessManager *tiliManager;
    QNetworkAccessManager *nameManager;
    QByteArray webToken;
    QJsonArray jsonArray;
    QString type;
    double limit;
    QString fName;


};

#endif // DLL_TESTI_H
