#ifndef SERVERWOKER_H
#define SERVERWOKER_H

#include <QObject>
#include <QTcpSocket>

class ServerWoker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWoker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);

signals:
    void logMessage(const QString &msg);


private:
    QTcpSocket *m_serverSocket;

public slots:
    void onReadyRead();
    void sendMessage(const QString &text,const QString &type = "message");
};

#endif // SERVERWOKER_H
