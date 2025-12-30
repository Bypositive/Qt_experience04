#include "chatserver.h"
#include "serverworker.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
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

    // 记录连接信息
    QString clientAddress = worker->getSocket() ?
                                worker->getSocket()->peerAddress().toString() : "未知";
    emit logMessage("--------------------------------------------");
    emit logMessage(QString("新的TCP连接来自: %1").arg(clientAddress));
    emit logMessage("--------------------------------------------");

    connect(worker, &ServerWorker::disconnectedFromClient, this, [this, worker](){
        userDisconnected(worker);
    });

    connect(worker, &ServerWorker::jsonReceived, this, [this, worker](const QJsonObject &json){
        jsonReceived(worker, json);
    });

    connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);

    m_clients.append(worker);
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &json)
{
    Q_ASSERT(sender);

    const QJsonValue typeVal = json.value("type");
    if (typeVal.isNull() || !typeVal.isString())
        return;

    const QString type = typeVal.toString();
    const QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    if (type == "login") {
        // 用户登录
        const QString userName = json.value("userName").toString();
        if (userName.isEmpty()) {
            logClientAction("login_failed", "", "无效的用户名", sender);
            return;
        }
        sender->setUserName(userName);

        // 记录登录日志
        logClientAction("login", userName, "用户登录", sender);

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
        if (text.isEmpty()) {
            logClientAction("message_failed", sender->getUserName(), "空消息", sender);
            return;
        }

        // 记录消息日志
        logClientAction("message", sender->getUserName(), text, sender);

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
        // 记录登出日志
        logClientAction("logout", userName, "用户退出", sender);

        // 通知其他用户该用户已离开
        QJsonObject message;
        message["type"] = "userLeft";
        message["userName"] = userName;
        broadcast(message, sender);
    } else {
        // 未登录就断开的情况
        logClientAction("disconnect", "未登录用户", "TCP连接断开", sender);
    }

    m_clients.removeAll(sender);
    sender->deleteLater();
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
    emit logMessage("--------------------------------------------");
    emit logMessage("服务器正在关闭...");
    emit logMessage(QString("当前在线用户数：%1").arg(m_clients.size()));
    emit logMessage("--------------------------------------------\n");

    // 使用新的公共方法断开连接
    for (ServerWorker *client : m_clients) {
        client->disconnectClient();
    }

    // 等待所有客户端断开
    QCoreApplication::processEvents();

    close();

    emit logMessage("--------------------------------------------");
    emit logMessage("服务器已成功关闭");
    emit logMessage("--------------------------------------------");
}

void ChatServer::logClientAction(const QString &action, const QString &userName,
                                 const QString &content, ServerWorker *sender)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString clientInfo = "";

    if (sender && sender->getSocket()) {
        clientInfo = QString("IP: %1:%2")
        .arg(sender->getSocket()->peerAddress().toString())
            .arg(sender->getSocket()->peerPort());
    }

    QString actionText;
    if (action == "login") {
        actionText = "login";
    } else if (action == "logout") {
        actionText = "logout";
    } else if (action == "message") {
        actionText = "message";
    } else if (action == "login_failed") {
        actionText = "login_failed";
    } else if (action == "message_failed") {
        actionText = "message_failed";
    } else if (action == "disconnect") {
        actionText = "disconnect";
    }

    emit logMessage("--------------------------------------------");
    emit logMessage(QString("用户名：%1").arg(userName.isEmpty() ? "未知" : userName));
    emit logMessage(QString("时间：%1").arg(currentTime));
    emit logMessage(QString("动作：%1").arg(actionText));
    emit logMessage(QString("内容：%1").arg(content));
    if (!clientInfo.isEmpty()) {
        emit logMessage(QString("客户端信息：%1").arg(clientInfo));
    }
    emit logMessage("--------------------------------------------\n");
}
