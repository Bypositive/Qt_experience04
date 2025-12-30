#include "serverworker.h"
#include <QDataStream>
#include <QJsonObject>
#include <QJsonParseError>

ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
{
    m_serverSocket = new QTcpSocket(this);

    connect(m_serverSocket, &QTcpSocket::readyRead, this, &ServerWorker::onReadyRead);
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectFromClient);
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

void ServerWorker::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_12);
    for(;;){
        socketStream.startTransaction();
        socketStream >> jsonData;
        if(socketStream.commitTransaction()){
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject()) {
                    emit jsonReceived(jsonDoc.object());
                }
            } else {
                emit logMessage("收到无效消息: " + QString::fromUtf8(jsonData));
            }
        } else {
            break;
        }
    }
}

void ServerWorker::disconnectFromClient()
{
    m_serverSocket->deleteLater();
    emit disconnectedFromClient();
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    if(m_serverSocket->state() != QAbstractSocket::ConnectedState)
        return;

    QDataStream serverStream(m_serverSocket);
    serverStream.setVersion(QDataStream::Qt_5_12);
    serverStream << QJsonDocument(json).toJson(QJsonDocument::Compact);
}
