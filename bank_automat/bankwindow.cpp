 #include "bankwindow.h"
#include "ui_balance.h"
#include "ui_bankwindow.h"
#include "kortinlukija.h"
#include "withdraw.h"
#include "transactions.h"
#include <QTimer>
#include <QDate>


bankWindow::bankWindow(Dll_testi* ptr, QWidget *parent)
    : QDialog(parent)
    , rest_ptr(ptr)
    , ui(new Ui::bankWindow)
{
    qDebug()<<"current token bankwindow = "<<rest_ptr->currentToken();
    ui->setupUi(this);
    qDebug()<<"Bankki";
    setWindowTitle("Bank");
    connect(rest_ptr, SIGNAL(sendName(QString)), this, SLOT(getName(QString)));
    rest_ptr->getName();

    connect(ui->nostoButton,SIGNAL(clicked(bool)),this,SLOT(withdrawMoney()));
    connect(ui->showBalanceButton,SIGNAL(clicked(bool)),this,SLOT(showBalance()));
    connect(ui->transactionsButton,SIGNAL(clicked(bool)),this,SLOT(showTransactions()));
    connect(ui->logOutButton,SIGNAL(clicked(bool)),this,SLOT(logOut()));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(paivitaKelloJaPVM()));
    timer->start(100);

    timeri = new QTimer(this);
    connect(timeri, SIGNAL(timeout()), this, SLOT(logOut()));
    timeri->start(30000);

    ui->labelTervetuloa->setStyleSheet("color: white;");
    ui->labelKello->setStyleSheet("color: white;");
    ui->labelPVM->setStyleSheet("color: white;");
    ui->labelNimi->setStyleSheet("color: white;");


    QPixmap kuva3(":///monitor.jpg");

    if (kuva3.isNull()) {
        qDebug() << "Kuvan lataaminen epäonnistui";
            return;
    }

    ui->labelKuva3->setPixmap(kuva3);
    ui->labelKuva3->setScaledContents(true);
}

bankWindow::~bankWindow()
{
    delete ui;
}

void bankWindow::showBalance()
{
    qDebug()<<"Show balance";
    balance *Balance = new balance(fName, rest_ptr, this);
    timeri->stop();
    timeri->start(30000);
    Balance->show();
}

void bankWindow::withdrawMoney()
{
    qDebug()<<"Withdraw money";
    withdraw *Withdraw = new withdraw(rest_ptr, this);
    timeri->stop();
    timeri->start(30000);
    Withdraw->show();
}

void bankWindow::showTransactions()
{
    qDebug()<<"Show transactions";
    transactions *Transactions = new transactions(fName, rest_ptr, this);
    timeri->stop();
    timeri->start(30000);
    Transactions->show();
}
void bankWindow::paivitaKello()
{
    QTime aika = QTime::currentTime();
    QString kellonaika = aika.toString("hh:mm:ss");
    ui->labelKello->setText(kellonaika);
}
void bankWindow::paivitaKelloJaPVM()
{
    paivitaKello();

    QDate date = QDate::currentDate();
    QString PVM = date.toString("dd.MM.yyyy");
    ui->labelPVM->setText(PVM);
}
void bankWindow::logOut()
{

    this->close();
    qDebug()<<"Bank Log out";
}
void bankWindow::getName(QString f){
    qDebug()<<"Got name!";
    fName = f;
    qDebug()<<fName;
    ui->labelNimi->setText(fName +"!");
    qDebug()<<f;
}





