#include "kortinlukija.h"
#include "ui_kortinlukija.h"
#include <QDebug>
#include <QTimer>
#include <QDate>


KortinLukija::KortinLukija(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KortinLukija)
{

    ui->setupUi(this);
    setWindowTitle("Kirjaudu sisään");

    ptr_dll = new Dialog(this);
    ptr = new Kortinlukudll(this);
    rest_ptr = new Dll_testi(this);
    ptr->openSerialPort();
    connect(ptr, SIGNAL(sendNumber(QString)),this, SLOT(sendCardSignal(QString)));
    connect(ptr_dll,SIGNAL(sendString(QString)),SLOT(handleDLLSignal(QString)));
    connect(rest_ptr, SIGNAL(sendResponse(bool)),this, SLOT(receiveResponse(bool)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(paivitaKelloJaPVM()));
    timer->start(100);

    ui->labelSyotaKortti->setStyleSheet("color: white;");
    ui->labelKello->setStyleSheet("color: white;");
    ui->labelPVM->setStyleSheet("color: white;");
    QPixmap kuva1(":///Bank_automat_drawing.jpg");
     QPixmap kuva2(":///BankCard.jpg");

    if (kuva1.isNull() || kuva2.isNull()) {
        qDebug() << "Kuvan lataaminen epäonnistui";
            return;
    }

    ui->labelKuva1->setPixmap(kuva1);
    ui->labelKuva1->setScaledContents(true);
    ui->labelKuva2->setPixmap(kuva2);
    ui->labelKuva2->setScaledContents(true);
}


KortinLukija::~KortinLukija()
{
    delete ui;
    delete ptr_dll;
    delete ptr;
    delete rest_ptr;
}

void KortinLukija::sendCardSignal(QString num) {

    qDebug() << "Korttisignaali lähetetty, korttinumero:" << num;
    cardNumber = num;
    ptr_dll->startTime();
    ptr_dll->show();
}


void KortinLukija::bankLogIn()
{
    qDebug()<<"Bank Log In";
    bankWindow *BankWindow = new bankWindow(rest_ptr, this);
    BankWindow->show();
}

void KortinLukija::handleDLLSignal(QString s)
{
    oikeaPinKoodi = s;
    qDebug()<<"Oikea pin koodi = "<<oikeaPinKoodi;
    qDebug()<<"Kortti"<<cardNumber;
    qDebug()<<"Pin"<<s;
    rest_ptr->login(cardNumber, oikeaPinKoodi);
}
void KortinLukija::receiveResponse(bool e)
{
    qDebug()<<"Login response = "<<e;
    qDebug()<<"Oikea pin koodi = "<<oikeaPinKoodi;
    emit sendPin(e);
    if(e == true){
        qDebug()<<"Mo "<<cardNumber;
        bankLogIn();
        qDebug()<<"Kirjauduttu Bankkiin";
    }
}


void KortinLukija::paivitaKello()
{
    QTime aika = QTime::currentTime();
    QString kellonaika = aika.toString("hh:mm:ss");
    ui->labelKello->setText(kellonaika);
}
void KortinLukija::paivitaKelloJaPVM()
{
    paivitaKello();

    QDate date = QDate::currentDate();
    QString PVM = date.toString("dd.MM.yyyy");
    ui->labelPVM->setText(PVM);
}


