#include "dialog.h"
#include "qobjectdefs.h"
#include "ui_dialog.h"
#include <QTimer>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Pin");
    if (!lukittu){
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
        connect(ui->EnterButton, SIGNAL(clicked(bool)),this,SLOT(enterButtonClicked()));
        connect(ui->BackButton, SIGNAL(clicked(bool)),this,SLOT(backButtonClicked()));

        connect(ui->EnterButton, SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
        connect(parent, SIGNAL(sendPin(bool)),this, SLOT(receivePin(bool)));
    }

}
void Dialog::startTime(){
    timeri = new QTimer(this);
    connect(timeri, SIGNAL(timeout()), this, SLOT(shutdown()));
    timeri->start(10000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::clickHandler()
{
    QString s= ui->lineEdit->text();
}

void Dialog::numberButtonClicked()
{
    QPushButton *nappi = qobject_cast<QPushButton*>(sender());
    if (nappi) {
        if(!lukittu){
            //timeri->stop();
            //timeri->start(10000);
            QString numero = nappi->text();
            QString nykyinenPinKoodi = ui->lineEdit->text();
            ui->lineEdit->setText(nykyinenPinKoodi + numero);
        }
        else{
            qDebug() <<"Lukittu ota yhteyttä pankkiin";
        }
    }

}

void Dialog::backButtonClicked()
{
    QString nykyinenPinKoodi = ui->lineEdit->text();
    if (!nykyinenPinKoodi.isEmpty()) {
        if(!lukittu){
            nykyinenPinKoodi.chop(1);
            ui->lineEdit->setText(nykyinenPinKoodi);
            //timeri->stop();
            //timeri->start(10000);
        }
        else{
            qDebug() <<"Lukittu ota yhteyttä pankkiin";
        }
    }
}


void Dialog::receivePin(bool p){
    qDebug()<<"Pin received";
    kortti = p;
    static int yritystenMaara = 3;
    if(!lukittu){
        if(!ui->lineEdit->text().isEmpty()){
            qDebug()<<"S "<<s;
            qDebug()<<"kortti "<<kortti;
            if (kortti == true) {
                qDebug() << "Oikea PIN-koodi. Pääsy myönnetty.";
                ui->lineEdit->text();
                ui->label->setText("Oikea PIN-koodi. Pääsy myönnetty.");
                ui->lineEdit->clear();
                ui->label->clear();
                ui->label2->clear();
                yritystenMaara = 3;
                close();
            }

            else if (kortti == false){
                yritystenMaara--;
                qDebug() << "Väärä PIN-koodi. Yritä uudelleen. "<<kortti;
                ui->lineEdit->clear();

                if (yritystenMaara > 0) {
                    ui->label->setText("Väärä PIN-koodi. Yritä uudelleen.");
                    ui->label2->setText("Yrityksiä jäljellä: " + QString::number(yritystenMaara));
                } else {
                    qDebug() << "Väärä PIN-koodi.";
                    ui->label->setText("Liian monta yritystä. e lukittu.");
                    ui->label2->setText("Ota yhteyttä pankkiin");
                    ui->lineEdit->setEnabled(false);
                    lukittu = true;
                }
            }
        }
    }
    else{
        qDebug() <<"Lukittu ota yhteyttä pankkiin";
    }
}

void Dialog::enterButtonClicked()
{
    s = ui->lineEdit->text();
    qDebug()<<"PinUiDll Pin lineeditissa = "<<s;
    emit sendString(s);
    //timeri->stop();
    //timeri->start(10000);
}

void Dialog::shutdown(){
    qDebug()<<"Close";
    timeri->stop();
    this->close();
}
