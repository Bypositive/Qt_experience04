#include "serverworker.h"
#include <QDataStream>
#include <QJsonObject>

ServerWoker::ServerWoker(QObject *parent)
    : QObject{parent}
{
    m_serverSocket =new QTcpSocket(this);

    connect(m_serverSocket,&QTcpSocket::readyRead,this,&ServerWoker::onReadyRead);
}

bool ServerWoker::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

void ServerWoker::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_12);
    for(;;){
        socketStream.startTransaction();
        socketStream>>jsonData;
        if(socketStream.commitTransaction()){
            emit logMessage(QString::fromUtf8(jsonData));
            sendMessage("已收到信息~~~");
        }else{
            break;

        }
    }
}

void ServerWoker::sendMessage(const QString &text, const QString &type)
{
    if(m_serverSocket->state()!=QAbstractSocket::ConnectedState)
        return;
    if(!text.isEmpty()){
        QDataStream serverStream(m_serverSocket);
        serverStream.setVersion(QDataStream::Qt_5_12);
        QJsonObject message;
        message["type"]=type;
        message["text"]=text;
        serverStream << QJsonDocument(message).toJson();
    }
}
