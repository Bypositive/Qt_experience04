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
                } else {
                    emit logMessage("收到非JSON对象数据");
                }
            } else {
                emit logMessage(QString("JSON解析错误: %1").arg(parseError.errorString()));
            }
        } else {
            break;
        }
    }
}

// 公共方法断开连接
void ServerWorker::disconnectClient()
{
    if (m_serverSocket && m_serverSocket->state() == QAbstractSocket::ConnectedState) {
        m_serverSocket->disconnectFromHost();
    }
}

// 私有槽函数，当socket断开时调用
void ServerWorker::disconnectFromClient()
{
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
