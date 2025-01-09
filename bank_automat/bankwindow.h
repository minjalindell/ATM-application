#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>
#include "dll_testi.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class bankWindow;
}
QT_END_NAMESPACE

class bankWindow : public QDialog
{
    Q_OBJECT

public:
    bankWindow(Dll_testi* ptr, QWidget *parent = nullptr);
    ~bankWindow();
    QString otherSum;
    Dll_testi* rest_ptr;
    QString fName;

private slots:
    void showBalance();
    void withdrawMoney();
    void showTransactions();
    void logOut();
    void paivitaKelloJaPVM();
    void paivitaKello();
    void getName(QString);

private:
    Ui::bankWindow *ui;
    QTimer *timer;
    QTimer *timeri;
};

#endif // BANKWINDOW_H

