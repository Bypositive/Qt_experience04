#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDateTime>
#include <QCoreApplication>  // 添加这行
#include "serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    void sendJson(ServerWorker *destination, const QJsonObject &message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    QVector<ServerWorker*> m_clients;

signals:
    void logMessage(const QString& msg);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender, const QJsonObject &json);
    void userDisconnected(ServerWorker *sender);

private:
    void broadcast(const QJsonObject &message, ServerWorker *exclude = nullptr);
    void logClientAction(const QString &action, const QString &userName,
                         const QString &content = "", ServerWorker *sender = nullptr);
};

#endif // CHATSERVER_H
