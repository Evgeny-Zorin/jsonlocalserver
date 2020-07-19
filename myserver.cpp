#include "myserver.h"

myserver::myserver(QObject *parent) :
    QTcpServer(parent)
{
    if(listen(QHostAddress::Any, 7777)){
        qDebug() <<"Listening...";
    }
    else{
        qDebug() <<"Error while starting: "<< errorString();
    }
}

void myserver::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
        connect(socket, SIGNAL(readyRead()),this, SLOT(onReadyRead()));
        connect(socket, SIGNAL(disconnected()),this, SLOT(onDisconnected()));
    qDebug() << socketDescriptor << "Client connected.";
    socket->write("{\"type\":\"connect\",\"status\":\"True\"}");
    qDebug() << "Send client connect status: True";


}

void myserver::startServer()
{
}

void myserver::onReadyRead()
{
    //QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    //qDebug() << socket->readAll();
    data = socket->readAll();
    qDebug() << data;
     doc = QJsonDocument::fromJson(data, &docError);
     if(docError.errorString().toInt() == QJsonParseError::NoError){
         if((doc.object().value("type").toString() == "select") && (doc.object().value("params").toString() == "TestFish")){
             QFile file;
             file.setFileName("C:\\TestFish.json");
             if(file.open(QIODevice::ReadOnly|QFile::Text)){
                 QByteArray fromFile = file.readAll();
                 QByteArray itog = "{\"type\":\"resultSelect\",\"result\":" + fromFile + "}";
                 socket->write(itog);
                 socket->waitForBytesWritten(250);
             }
             file.close();         }
     }
}

void myserver::onDisconnected()
{
    qDebug() << "Disconnect";
    socket->deleteLater();  //сокет удалится приложением, когда это будет возможно
}


















































