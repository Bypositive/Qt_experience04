#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString getUserName() const { return userName; }
    void setUserName(const QString &name) { userName = name; }
    QTcpSocket* getSocket() const { return m_serverSocket; }

    // 添加一个公共方法来断开连接
    void disconnectClient();

signals:
    void logMessage(const QString &msg);
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();

private slots:
    void onReadyRead();
    void disconnectFromClient();

private:
    QTcpSocket *m_serverSocket;
    QString userName;

public slots:
    void sendJson(const QJsonObject &json);
};

#endif // SERVERWORKER_H
