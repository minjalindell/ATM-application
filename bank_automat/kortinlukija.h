#ifndef KORTINLUKIJA_H
#define KORTINLUKIJA_H

#include <QMainWindow>
#include "bankwindow.h"
#include "balance.h"
#include "dialog.h"
#include "kortinlukudll.h"
#include "dll_testi.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class KortinLukija;
}
QT_END_NAMESPACE

class KortinLukija : public QMainWindow
{
    Q_OBJECT

public:
    KortinLukija(QWidget *parent = nullptr);
    ~KortinLukija();
    QString cardNumber;
    bool notLoggedIn = true;
    QString oikeaPinKoodi;
    QString response;



signals:
    void cardSignal(const QString &cardNumber);
    void pinSignal(const QString &pinCode);
    void sendPin(bool);


public slots:
    void sendCardSignal(QString);


private slots:
    void bankLogIn();
    void handleDLLSignal(QString);
    void receiveResponse(bool);
    void paivitaKelloJaPVM();
    void paivitaKello();


private:
    Ui::KortinLukija *ui;
    Dialog * ptr_dll;
    Kortinlukudll *ptr;
    Dll_testi *rest_ptr;
    QTimer *timer;
};
#endif // KORTINLUKIJA_H
