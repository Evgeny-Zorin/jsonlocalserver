#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>

class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = 0);
    void incomingConnection(qintptr socketDescriptor) override; //действия при подлкючении нового клиента
    void startServer();
public slots:
    void onReadyRead();
    void onDisconnected();
public:
    QTcpSocket* socket;
    QByteArray data;

    QJsonDocument doc;
    QJsonParseError docError;

};

#endif // MYSERVER_H
