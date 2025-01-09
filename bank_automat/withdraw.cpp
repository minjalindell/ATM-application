#include "withdraw.h"
#include "ui_withdraw.h"
#include "otherwithdrawal.h"


withdraw::withdraw(Dll_testi* ptr, QWidget *parent) :
    QDialog(parent),
    rest_ptr(ptr),
    ui(new Ui::withdraw)
{
    qDebug()<<"Let's withdraw";
    ui->setupUi(this);
    setWindowTitle("Nosto");
    connect(ui->withdrawBackButton,SIGNAL(clicked(bool)),this,SLOT(previousPage2()));
    connect(ui->pushButton10,SIGNAL(clicked(bool)),this,SLOT(pushButton10clicked()));
    connect(ui->pushButton20,SIGNAL(clicked(bool)),this,SLOT(pushButton20clicked()));
    connect(ui->pushButton50,SIGNAL(clicked(bool)),this,SLOT(pushButton50clicked()));
    connect(ui->pushButton100,SIGNAL(clicked(bool)),this,SLOT(pushButton100clicked()));
    connect(ui->pushButtonOther,SIGNAL(clicked(bool)),this,SLOT(pushButtonOtherclicked()));
    rest_ptr->saldo();
    timeri = new QTimer(this);
    connect(timeri, SIGNAL(timeout()), this, SLOT(previousPage2()));
    timeri->start(10000);
}

withdraw::~withdraw()
{
    delete ui;

}

void withdraw::previousPage2()
{
    if(ui->withdrawBackButton,SIGNAL(clicked(bool))){
        this->close();
    }
}

void withdraw::pushButton10clicked()
{
    double num = 10;
    //ui->label->setText("Nostettu 10e");
    qDebug("Nosto 10e");
    rest_ptr->nosto(num);
    connect(rest_ptr, SIGNAL(send_response(QString)), this, SLOT(receive_response(QString)));
    timeri->stop();
    timeri->start(10000);
}

void withdraw::pushButton20clicked()
{
    double num = 20;
    //ui->label->setText("Nostettu 20e");
    qDebug("Nosto 20e");
    rest_ptr->nosto(num);
    connect(rest_ptr, SIGNAL(send_response(QString)), this, SLOT(receive_response(QString)));
    timeri->stop();
    timeri->start(10000);
}

void withdraw::pushButton50clicked()
{
    double num = 50;
    //ui->label->setText("Nostettu 50e");
    qDebug("Nosto 50e");
    rest_ptr->nosto(num);
    connect(rest_ptr, SIGNAL(send_response(QString)), this, SLOT(receive_response(QString)));
    timeri->stop();
    timeri->start(10000);
}

void withdraw::pushButton100clicked()
{
    double num = 100;
    //ui->label->setText("Nostettu 100e");
    qDebug("Nosto 100e");
    rest_ptr->nosto(num);
    connect(rest_ptr, SIGNAL(send_response(QString)), this, SLOT(receive_response(QString)));
    timeri->stop();
    timeri->start(10000);
}

void withdraw::pushButtonOtherclicked()
{
    qDebug()<<"Withdraw other sum";
    otherWithdrawal *OtherWithdrawal = new otherWithdrawal(rest_ptr, this);
    timeri->stop();
    timeri->start(10000);
    OtherWithdrawal->show();
}

void withdraw::receive_response(QString e){
    ui->label->setText(e);
}
