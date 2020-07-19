#ifndef MYSERVER_H
#define MYSERVER_H



#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QList>
#include <QTime>
#include "classmessege.h"

class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = 0);
    void incomingConnection(qintptr socketDescriptor) override; //действия при подлкючении нового клиента
public slots:
    void onReadyRead();
    void onDisconnected();
public:
    QTcpSocket* socket;
    QByteArray bData;

    QJsonDocument doc;
    QJsonParseError docError;
private:
    MessegeController controller;
};

#endif // MYSERVER_H
