#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>
#include "dll_testi.h"
#include<QStandardItemModel>

namespace Ui {
class transactions;
}

class transactions : public QDialog
{
    Q_OBJECT

public:
    explicit transactions(QString, Dll_testi* ptr, QWidget *parent = nullptr);
    ~transactions();
    Dll_testi *rest_ptr;

private slots:
    void previousPage3();
    void showTransactionData();
private:
    Ui::transactions *ui;
    QJsonArray transactionsData;
    QStandardItemModel *table_model;
    QTimer *timeri;

};

#endif // TRANSACTIONS_H
