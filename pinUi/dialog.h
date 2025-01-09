#ifndef DIALOG_H
#define DIALOG_H
#include "pinkoodi3DLL_global.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class PINKOODI3DLL_EXPORT Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString s;
    bool kortti = false;
    bool lukittu = false;

    void startTime();
signals:
    void sendString(QString);
    void sendPin(bool);

private slots:
    void clickHandler();
    void numberButtonClicked();
    void backButtonClicked();
    void enterButtonClicked();
    void receivePin(bool);
    void shutdown();
private:
    Ui::Dialog *ui;
    QTimer *timeri;
};

#endif // DIALOG_H
