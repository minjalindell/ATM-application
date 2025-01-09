#ifndef OTHERWITHDRAWAL_H
#define OTHERWITHDRAWAL_H

#include <QDialog>
#include "dll_testi.h"

namespace Ui {
class otherWithdrawal;
}

class otherWithdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit otherWithdrawal(Dll_testi* ptr, QWidget *parent = nullptr);
    ~otherWithdrawal();
    QString otherSum;
    Dll_testi *rest_ptr;

signals:
    void sendOtherSignal(QString);

private slots:
    void previousPage4();
    void withdrawOtherSum();
    void numberButtonClicked();
    void DelButtonClicked();
    void receive_response(QString);


private:
    Ui::otherWithdrawal *ui;
    QTimer *timeri;
    QString response;
};

#endif // OTHERWITHDRAWAL_H
