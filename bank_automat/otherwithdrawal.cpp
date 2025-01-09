#include "otherwithdrawal.h"
#include "ui_otherwithdrawal.h"
#include <QMessageBox>

otherWithdrawal::otherWithdrawal(Dll_testi* ptr, QWidget *parent) :
    QDialog(parent),
    rest_ptr(ptr),
    ui(new Ui::otherWithdrawal)
{
    ui->setupUi(this);
    setWindowTitle("Muu nosto");
    connect(ui->backButtonOther,SIGNAL(clicked(bool)),this,SLOT(previousPage4()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(withdrawOtherSum()));
    timeri = new QTimer(this);
    connect(timeri, SIGNAL(timeout()), this, SLOT(previousPage4()));
    timeri->start(10000);

    connect(ui->Number1, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number2, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number3, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number4, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number5, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number6, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number7, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number8, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number9, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->Number0, SIGNAL(clicked(bool)),this,SLOT(numberButtonClicked()));
    connect(ui->DelButton, SIGNAL(clicked(bool)),this,SLOT(DelButtonClicked()));
    connect(rest_ptr, SIGNAL(send_response(QString)), this, SLOT(receive_response(QString)));

}

otherWithdrawal::~otherWithdrawal()
{
    delete ui;
}


void otherWithdrawal::previousPage4()
{
    if(ui->backButtonOther,SIGNAL(clicked(bool))){
        //as
        this->close();
    }
}

void otherWithdrawal::withdrawOtherSum()
{
    otherSum = ui->lineEditOther->text();
    qDebug()<<"Ok painettu";
    if (otherSum.isEmpty()) {
        qDebug() << "Summaa ei syötetty!!";
        return;

    }
    double num = otherSum.toDouble();
    this->close();
    rest_ptr->nosto(num);
    timeri->stop();
    timeri->start(10000);


}

void otherWithdrawal::numberButtonClicked()
{
    QPushButton *nappi = qobject_cast<QPushButton*>(sender());
    if (nappi) {
            timeri->stop();
            timeri->start(10000);
            QString numero = nappi->text();
            QString nykyinenPinKoodi = ui->lineEditOther->text();
            ui->lineEditOther->setText(nykyinenPinKoodi + numero);
        }
}

void otherWithdrawal::DelButtonClicked()
{
    QString nykyinenPinKoodi = ui->lineEditOther->text();
    if (!nykyinenPinKoodi.isEmpty()) {
            nykyinenPinKoodi.chop(1);
            ui->lineEditOther->setText(nykyinenPinKoodi);
            timeri->stop();
            timeri->start(10000);
    }
}

void otherWithdrawal::receive_response(QString e)
{
    qDebug()<<"response";
    QMessageBox msgBox;
    msgBox.setText(e);
    msgBox.exec();
}


