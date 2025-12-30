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

signals:
    void logMessage(const QString &msg);
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();

private slots:
    void onReadyRead();

private:
    QTcpSocket *m_serverSocket;
    QString userName;

public slots:
    void sendJson(const QJsonObject &json);
    void disconnectFromClient();
};

#endif // SERVERWORKER_H
