#include "chatserver.h"
#include "serverworker.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ChatServer::ChatServer(QObject *parent):
    QTcpServer(parent)
{
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if(!worker->setSocketDescriptor(socketDescriptor)){
        worker->deleteLater();
        return;
    }

    connect(worker, &ServerWorker::disconnectedFromClient, this, [this, worker](){
        userDisconnected(worker);
    });

    connect(worker, &ServerWorker::jsonReceived, this, [this, worker](const QJsonObject &json){
        jsonReceived(worker, json);
    });

    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);

    m_clients.append(worker);
    emit logMessage("新的用户连接成功~~~");
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &json)
{
    Q_ASSERT(sender);

    const QJsonValue typeVal = json.value("type");
    if (typeVal.isNull() || !typeVal.isString())
        return;

    const QString type = typeVal.toString();

    if (type == "login") {
        // 用户登录
        const QString userName = json.value("userName").toString();
        if (userName.isEmpty()) {
            return;
        }
        sender->setUserName(userName);

        // 通知所有人有新用户加入
        QJsonObject message;
        message["type"] = "userJoined";
        message["userName"] = userName;
        broadcast(message, sender);

        // 给新用户发送欢迎消息
        QJsonObject welcomeMessage;
        welcomeMessage["type"] = "loginSuccess";
        welcomeMessage["userName"] = userName;
        sendJson(sender, welcomeMessage);

        // 给新用户发送当前用户列表
        QJsonArray userList;
        for (ServerWorker *client : m_clients) {
            if (!client->getUserName().isEmpty()) {
                userList.append(client->getUserName());
            }
        }
        QJsonObject userListMessage;
        userListMessage["type"] = "userList";
        userListMessage["users"] = userList;
        sendJson(sender, userListMessage);

    } else if (type == "message") {
        // 聊天消息
        const QString text = json.value("text").toString();
        if (text.isEmpty())
            return;

        QJsonObject message;
        message["type"] = "message";
        message["text"] = text;
        message["sender"] = sender->getUserName();
        message["timestamp"] = QDateTime::currentDateTime().toString("hh:mm:ss");
        broadcast(message, sender);
    }
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    const QString userName = sender->getUserName();
    if (!userName.isEmpty()) {
        // 通知其他用户该用户已离开
        QJsonObject message;
        message["type"] = "userLeft";
        message["userName"] = userName;
        broadcast(message, sender);
    }

    m_clients.removeAll(sender);
    sender->deleteLater();
    emit logMessage("用户断开连接: " + userName);
}

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *client : m_clients) {
        if (client == exclude)
            continue;
        sendJson(client, message);
    }
}

void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}

void ChatServer::stopServer()
{
    for (ServerWorker *client : m_clients) {
        client->disconnectFromClient();
    }
    close();
}
