#ifndef CLASSMESSEGE_H
#define CLASSMESSEGE_H
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QList>
#include <QTime>

#define F_Time "time"
#define F_Mes "msg"

class classMessege
{
public:
    classMessege(QJsonObject jObj);
    QJsonObject toJsonObject();
private:
    QString _msg;
    QTime _time;
};

class MessegeController{
public:
    void clearList();   //очистка истории
    void append(QByteArray json);   //добавит новую запись
    QByteArray getlist();  //вернет все значения
private:
    QList<classMessege> listMsg;

};

#endif // CLASSMESSEGE_H
