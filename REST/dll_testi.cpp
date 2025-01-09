#include "dll_testi.h"
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QJsonDocument>
#include <QtSql>
#include <QDateTime>

Dll_testi::Dll_testi(QObject *parent): QObject(parent)
{

}

void Dll_testi::login(QString uname, QString passwd)
{
    if(uname == "0600096"){
        accountNumber = "123";
        type = "Debit";
    }
    else if(uname == "06000894"){
        accountNumber = "852";
        type = "Credit";
    }

    QJsonObject jsonObj;
    jsonObj.insert("pin",passwd);
    jsonObj.insert("cardNumber",uname);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Dll_testi::loginSlot(QNetworkReply *reply)
{
    bool response = false;
    qDebug()<<"LoginSlot";
    response_data=reply->readAll();
    if(response_data=="-4078" || response_data.length()==0){

        qDebug("Virhe tietoyhteydessä");
    }
    else{
        if(response_data!="{\"error\":\"cardNumber or pin missing\"}" && response_data != "false"){
            qDebug()<<"response"<<response_data;
            setWebToken(response_data);
            response = true;
            emit sendResponse(response);
        }
        else{
            qDebug()<<response_data;
            response = false;
            emit sendResponse(response);
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

void Dll_testi::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void Dll_testi::saldo(){
    qDebug()<<"saldo";
    QString site_url="http://localhost:3000/account/" + accountNumber;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    qDebug()<<"Webtoken ennen pyyntoa"<<webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    saldoManager = new QNetworkAccessManager(this);

    connect(saldoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));

    reply = saldoManager->get(request);
}

QByteArray Dll_testi::currentToken()
{
    return webToken;
}

void Dll_testi::saldoSlot(QNetworkReply *reply){
    qDebug()<<"Saldo slot";
    QByteArray responseData = reply->readAll();
    qDebug()<<"response = "<<responseData;
    QString responseString = QString::fromUtf8(responseData);

    // Attempt to parse the response data as JSON
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    qDebug()<<"jsonDoc = "<<jsonDocument;

    // Check if the JSON parsing was successful
    if (jsonDocument.isNull() || !jsonDocument.isArray()) {
        qDebug() << "Invalid JSON response:" << responseString;
        // Handle invalid JSON response accordingly
        return;
    }
    QJsonArray jsonArray = jsonDocument.array();

    if (jsonArray.isEmpty()) {
        qDebug() << "Empty JSON array received";
        return;
    }
    foreach (const QJsonValue& value, jsonArray) {
        QJsonObject json_obj = value.toObject();
        qDebug()<<"Json object = "<<json_obj;
        qDebug()<<"Json object []"<<json_obj["Balance"];
        qDebug()<<"Json object []"<<json_obj["Credit limit"];
        qDebug()<<json_obj["Balance"].toString();
        qDebug()<<json_obj["Credit limit"].toDouble();
        limit = json_obj["Credit limit"].toDouble();
        qDebug()<<"Credit limit = "<<limit;
        QString str = json_obj["Balance"].toString();
        balance = str.toDouble();
        if(balance != 0){
            emit sendBalance(type, balance);
        }
        else if(balance == 0){
            emit sendBalance(type, limit);
        }

    }

    reply->deleteLater();
    saldoManager->deleteLater();
}

void Dll_testi::nosto(double n){
    qDebug()<<"Nosto";
    double new_limit = 0;
    num = n;
    if (balance != 0) {
        double new_balance = 0;
        qDebug() << "Update balance";
        new_balance = balance - n;
        qDebug() << "balance =" << balance;
        qDebug() << "num =" << num;
        qDebug() << "new balance =" << new_balance;
        balance = new_balance;

        if (new_balance < 0) {
            qDebug() << "Ei tarpeeksi rahaa";
            emit send_response("Ei tarpeeksi rahaa");
            return;
        }
        else if(balance > 0){
            qDebug()<<"balance > 0";
            //balance = new_balance;
            qDebug()<<"Updated balance = "<<balance;

            QJsonObject jsonObject;
            jsonObject["Balance"] = balance;
            jsonObject["Type"] = type;
            jsonObject["Credit limit"] = limit;
            jsonObject["UserID"] = 1;
            qDebug()<<"json objects = "<<jsonObject["Balance"];

            // Convert the JSON object to a QByteArray
            QByteArray jsonData = QJsonDocument(jsonObject).toJson();

            // Construct the URL
            QString site_url = "http://localhost:3000/account/" + accountNumber;

            // Create a PUT request
            QNetworkRequest request;
            request.setUrl(QUrl(site_url));
            QByteArray myToken="Bearer "+webToken;
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            request.setRawHeader("Authorization", myToken);

            // Send the PUT request with the updated balance in the request body
            nostoManager = new QNetworkAccessManager(this);
            connect(nostoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));
            reply = nostoManager->put(request, jsonData);
        }
    } else if (limit != 0) {
        qDebug() << "Update limit";
        new_limit = limit - n;
        qDebug() << "Credit limit =" << limit;
        qDebug() << "num =" << num;
        qDebug() << "new limit =" << new_limit;
        limit = new_limit;

        if (new_limit < 0) {
            qDebug() << "Ei tarpeeksi rahaa";
            emit send_response("Ei tarpeeksi rahaa");
            return;
        }
        else if(limit > 0){
            qDebug() << "balance == 0";
            qDebug() << "new limit =" << new_limit;

            // Saldo on nolla, päivitetään luottoraja ja lähetetään päivitys palvelimelle
            limit = new_limit;

            // Luodaan JSON-objekti päivitetystä tiedosta
            QJsonObject jsonObject;
            jsonObject["Balance"] = balance;
            jsonObject["Type"] = type;
            jsonObject["creditLimit"] = limit; // Huomaa, että Credit limit on tässä samassa muodossa kuin tietokantataulussa
            jsonObject["UserID"] = 1;

            // Muunnetaan JSON-objekti QByteArrayksi
            QByteArray jsonData = QJsonDocument(jsonObject).toJson();
            qDebug() << "JsonData =" << jsonData;

            // Muodostetaan URL
            QString site_url = "http://localhost:3000/account/" + accountNumber;

            // Luodaan PUT-pyyntö
            QNetworkRequest request;
            request.setUrl(QUrl(site_url));
            QByteArray myToken = "Bearer " + webToken;
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            request.setRawHeader("Authorization", myToken);

            // Lähetetään PUT-pyyntö päivitetyllä luottorajalla pyynnön runkona
            nostoManager = new QNetworkAccessManager(this);
            connect(nostoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));
            reply = nostoManager->put(request, jsonData);
        }
    }



}

void Dll_testi::nostoSlot(QNetworkReply *reply){

    if (reply->error() == QNetworkReply::NoError) {
        if(balance != 0){
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

            if (!jsonDocument.isNull() && jsonDocument.isObject()) {
                    qDebug() << "Balance updated successfully. New balance:" << balance;
                    QString y = "Balance updated successfully. New balance:" +QString::number(balance);
                    emit send_response(y);
                    TransActionAdd();
            } else {
                qDebug() << "Error: Invalid JSON response";
            }
        }
        else if(balance == 0){
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

            if (!jsonDocument.isNull() && jsonDocument.isObject()) {
                qDebug() << "limit updated successfully. New limit:" << limit;
                QString y = "limit updated successfully. New limit:" +QString::number(limit);
                emit send_response(y);
                TransActionAdd();
            } else {
                qDebug() << "Error: Invalid JSON response";
            }
        }
    }

    reply->deleteLater();
    nostoManager->deleteLater();
}

void Dll_testi::TransActionAdd(){

    num = num * -1;
    qDebug()<<"transactions"<<limit;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Convert to string format
    QString currentDateTimeString = currentDateTime.toString(Qt::ISODate);

    qDebug() << "Current date and time:" << currentDateTimeString;

    QJsonObject jsonObject;
    jsonObject["id_receiver"] = "Pankki";
    jsonObject["type"] = type;
    jsonObject["transaction"] = "Nosto";
    jsonObject["amount"] = num;
    jsonObject["date_time"] = currentDateTimeString;
    jsonObject["AccountNumber"] = accountNumber;

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // Construct the URL
    QString site_url = "http://localhost:3000/transactions";

    // Create a POST request
    QNetworkRequest request;
    request.setUrl(QUrl(site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", myToken);

    // Send the POST request with the transaction data in the request body
    tiliManager = new QNetworkAccessManager(this);
    connect(tiliManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(TransactionSlot(QNetworkReply*)));
    reply = tiliManager->post(request, jsonData);

}
void Dll_testi::TransactionSlot(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        // Read the response data
        QByteArray responseData = reply->readAll();

        // Parse the JSON response
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

        // Check if the JSON parsing was successful and the response is an object
        if (!jsonDocument.isNull() && jsonDocument.isObject()) {
            // Extract any information you need from the JSON response
            QJsonObject jsonObject = jsonDocument.object();
            qDebug() << "Transaction response:" << jsonObject;
        } else {
            qDebug() << "Error: Invalid JSON response for transaction";
            // Additional error handling if needed
        }
    } else {
        qDebug() << "Error making transaction:" << reply->errorString();
        // Additional error handling if needed
    }
}

void Dll_testi::getTransaction(){
    qDebug()<<"Transaction";
    QString site_url="http://localhost:3000/transactions/" + accountNumber;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    qDebug()<<"Webtoken ennen pyyntoa"<<webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    tiliManager = new QNetworkAccessManager(this);

    connect(tiliManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(TiliSlot(QNetworkReply*)));

    reply = tiliManager->get(request);
}

void Dll_testi::TiliSlot(QNetworkReply *reply){

    QByteArray responseData = reply->readAll();
    qDebug() << "Response: " << responseData;

    // Attempt to parse the response data as JSON
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

    // Check if the JSON parsing was successful
    if (jsonDocument.isNull() || !jsonDocument.isArray()) {
        qDebug() << "Invalid JSON response:" << responseData;
        // Handle invalid JSON response accordingly
        return;
    }

    jsonArray = jsonDocument.array();

    if (jsonArray.isEmpty()) {
        qDebug() << "Empty JSON array received";
        return;
    }

    foreach (const QJsonValue &value, jsonArray) {
        QJsonObject json_obj = value.toObject();
        qDebug() << "Json object: " << json_obj;

        // Extract the required fields from the JSON object
        int idTransaction = json_obj["idTransaction"].toInt();
        QString id_receiver = json_obj["id_receiver"].toString();
        QString type = json_obj["type"].toString();
        QString transaction = json_obj["transaction"].toString();
        QString a = json_obj["amount"].toString();
        double amount = a.toDouble();
        QString date_time = json_obj["date_time"].toString();
        QString AccountNumber = json_obj["AccountNumber"].toString();

        // Perform further processing if needed
        qDebug() << "idTransaction:" << idTransaction;
        qDebug() << "id_receiver:" << id_receiver;
        qDebug() << "type:" << type;
        qDebug() << "transaction:" << transaction;
        qDebug() << "amount:" << amount;
        qDebug() << "date_time:" << date_time;
        qDebug() << "AccountNumber:" << AccountNumber;

        // Emit signals or perform other operations as necessary
        //emit sendTransactionInfo();
        emit transActionsReady();
    }

    // Clean up resources
    reply->deleteLater();
    tiliManager->deleteLater();
}

QJsonArray Dll_testi::getJsonArray() const
{
    return jsonArray;
}

void Dll_testi::getName(){
    qDebug()<<"nimi";
    QString site_url="http://localhost:3000/users/1";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    qDebug()<<"Webtoken ennen pyyntoa"<<webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    nameManager = new QNetworkAccessManager(this);

    connect(nameManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nameSlot(QNetworkReply*)));

    reply = nameManager->get(request);
}

void Dll_testi::nameSlot(QNetworkReply *reply){
    qDebug()<<"Name slot";
    QByteArray responseData = reply->readAll();
    qDebug()<<"response = "<<responseData;
    QString responseString = QString::fromUtf8(responseData);

    // Attempt to parse the response data as JSON
    QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
    qDebug()<<"jsonDoc = "<<jsonDocument;

    // Check if the JSON parsing was successful
    if (jsonDocument.isNull() || !jsonDocument.isArray()) {
        qDebug() << "Invalid JSON response:" << responseString;
        // Handle invalid JSON response accordingly
        return;
    }
    QJsonArray jsonArray = jsonDocument.array();

    if (jsonArray.isEmpty()) {
        qDebug() << "Empty JSON array received";
        return;
    }
    foreach (const QJsonValue& value, jsonArray) {
        QJsonObject json_obj = value.toObject();
        qDebug()<<"Json object = "<<json_obj;
        qDebug()<<"Json object []"<<json_obj["fname"];
        fName = json_obj["fname"].toString();
        qDebug()<<"name = "<<fName;
        emit sendName(fName);
    }

    reply->deleteLater();
    nameManager->deleteLater();
}
