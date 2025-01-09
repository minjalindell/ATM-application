#ifndef BALANCE_H
#define BALANCE_H

#include <QDialog>
#include "dll_testi.h"
#include<QStandardItemModel>


namespace Ui {
class balance;
}

class balance : public QDialog
{
    Q_OBJECT

public:
    explicit balance(QString, Dll_testi* ptr, QWidget *parent = nullptr);
    ~balance();
    Dll_testi *rest_ptr;

private slots:
    void previousPage();
    void receiveBalance(QString, double);

    void showTransactionData();
private:
    Ui::balance *ui;
    double Balance;
    QTimer *timeri;
    QJsonArray transactionsData;
};

#endif // BALANCE_H
