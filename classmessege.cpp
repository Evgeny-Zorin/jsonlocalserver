#include "classmessege.h"

classMessege::classMessege(QJsonObject jObj)
{
    _time = jObj.value(F_Time).toVariant().toTime();
    _msg = jObj.value(F_Mes).toString();
}

QJsonObject classMessege::toJsonObject()
{
    QJsonObject jObj;
    jObj.insert(F_Time, QJsonValue::fromVariant(_time));
    jObj.insert(F_Mes, QJsonValue::fromVariant(_msg));
    return jObj;
}

void MessegeController::clearList()
{
    listMsg.clear();
}

void MessegeController::append(QByteArray json)
{
    QJsonObject jMessege = QJsonDocument::fromJson(json).object();
    listMsg.append(classMessege(jMessege));
}

QByteArray MessegeController::getlist()
{
    QJsonArray jMessege;
    foreach(classMessege messege,  listMsg){
        jMessege.append(messege.toJsonObject());
    }
    return  QJsonDocument(jMessege).toJson();
}
