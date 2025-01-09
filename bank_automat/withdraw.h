#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QDialog>
#include "dll_testi.h"

namespace Ui {
class withdraw;
}

class withdraw : public QDialog
{
    Q_OBJECT

public:
    explicit withdraw(Dll_testi* ptr, QWidget *parent = nullptr);
    ~withdraw();
    Dll_testi *rest_ptr;

signals:
    void sendSum(double);


private slots:
    void previousPage2();
    void pushButton10clicked();
    void pushButton20clicked();
    void pushButton50clicked();
    void pushButton100clicked();
    void pushButtonOtherclicked();
    void receive_response(QString);
private:
    Ui::withdraw *ui;
    withdraw * ptr_OtherSum;
    QTimer *timeri;
};

#endif // WITHDRAW_H
