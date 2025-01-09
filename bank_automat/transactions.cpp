#include "transactions.h"
#include "ui_transactions.h"

transactions::transactions(QString fName, Dll_testi* ptr, QWidget *parent) :
    QDialog(parent),
    rest_ptr(ptr),
    ui(new Ui::transactions)
{
    ui->setupUi(this);
    setWindowTitle("Tilitapahtumat");
    connect(ui->transactionsBackButton,SIGNAL(clicked(bool)),
            this,SLOT(previousPage3()));

    rest_ptr->getTransaction();
    connect(rest_ptr, SIGNAL(transActionsReady()),this, SLOT(showTransactionData()));

    ui->label->setText("Hei " + fName + "! Tässä tilitapahtumasi:");

    timeri = new QTimer(this);
    connect(timeri, SIGNAL(timeout()), this, SLOT(previousPage3()));
    timeri->start(10000);
}

transactions::~transactions()
{
    delete ui;
}

void transactions::previousPage3()
{

    if(ui->transactionsBackButton,SIGNAL(clicked(bool))){
        this->close();
    }
}

void transactions::showTransactionData()
{
    transactionsData = rest_ptr->getJsonArray();
    qDebug()<<"Data = "<<transactionsData;
    QStandardItemModel *table_model = new QStandardItemModel(0, 7);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("idTransaction"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("AccountNumber"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("amount"));
    table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_time"));
    table_model->setHeaderData(4, Qt::Horizontal, QObject::tr("transaction"));
    table_model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_receiver"));
    table_model->setHeaderData(6, Qt::Horizontal, QObject::tr("type"));

    int rowCount = qMin(transactionsData.size(), 10);

    for (int row = 0; row < rowCount; ++row) {
        QJsonObject json_obj = transactionsData[row].toObject();

        QStandardItem *idTransactionItem = new QStandardItem(QString::number(json_obj["idTransaction"].toInt()));
        table_model->setItem(row, 0, idTransactionItem);
        QStandardItem *accountNumberItem = new QStandardItem(QString::number(json_obj["AccountNumber"].toInt()));
        table_model->setItem(row, 1, accountNumberItem);
        QStandardItem *amountItem = new QStandardItem(json_obj["amount"].toString());
        table_model->setItem(row, 2, amountItem);
        QStandardItem *dateTimeItem = new QStandardItem(json_obj["date_time"].toString());
        table_model->setItem(row, 3, dateTimeItem);
        QStandardItem *transactionItem = new QStandardItem(json_obj["transaction"].toString());
        table_model->setItem(row, 4, transactionItem);
        QStandardItem *idReceiverItem = new QStandardItem(json_obj["id_receiver"].toString());
        table_model->setItem(row, 5, idReceiverItem);
        QStandardItem *typeItem = new QStandardItem(json_obj["type"].toString());
        table_model->setItem(row, 6, typeItem);
    }

    ui->tableView->setModel(table_model);
}
