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
//    QString request = socket->readAll();
//    qDebug() << request;
//     if(docError.errorString().toInt() == QJsonParseError::NoError){
//         socket->write("HTTP/1.1 200 OK\r\n\r\n");
//         if(request.startsWith("GET")){
//             socket->write(controller.getlist());
//         }
//         else if(request.startsWith("PUT")){
//             QString data = request.section("\r\n\r\n",1,1);
//             controller.append(data.toUtf8());
//         }
//         else if(request.startsWith("DELETE")){
//             controller.clearList();
//         }
//     }
//old
     bData  = socket->readAll();
     doc = QJsonDocument::fromJson(bData, &docError);
       if(docError.errorString().toInt() == QJsonParseError::NoError){
         if((doc.object().value("type").toString() == "select") && (doc.object().value("params").toString() == "TestFish")){
             QFile file;
             file.setFileName("C:\\TestFish2.json");
             if(file.open(QIODevice::ReadOnly|QFile::Text)){
                 qDebug() << "file is open!";
                 QByteArray fromFile = file.readAll();
                 QByteArray itog = "{\"type\":\"resultSelect\",\"result\":" + fromFile + "}";
                 socket->write(itog);
                 socket->waitForBytesWritten(250);
             }
             else qDebug() <<" fail open file";
             file.close();         }
     }
}

void myserver::onDisconnected()
{
    qDebug() << "Disconnect";
    socket->deleteLater();  //сокет удалится приложением, когда это будет возможно
}
