#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage_2);

    // 设置默认值方便测试
    ui->serviceEdit_2->setText("localhost");
    ui->nameEdit_2->setText("乌鸡国3096");

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::readyRead);
}

void MainWindow::on_loginBtn_2_clicked()
{
    QString serverAddress = ui->serviceEdit_2->text();
    QString userName = ui->nameEdit_2->text();

    if (serverAddress.isEmpty() || userName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入服务器地址和昵称！");
        return;
    }

    m_userName = userName;
    m_socket->connectToHost(serverAddress, 1967);

    // 显示连接中状态
    ui->loginBtn_2->setEnabled(false);
    ui->loginBtn_2->setText("连接中...");
}

void MainWindow::connected()
{
    // 发送登录信息
    QJsonObject loginMessage;
    loginMessage["type"] = "login";
    loginMessage["userName"] = m_userName;
    sendJson(loginMessage);
}

void MainWindow::disconnected()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage_2);
    ui->loginBtn_2->setEnabled(true);
    ui->loginBtn_2->setText("登录");
    QMessageBox::information(this, "提示", "已断开与服务器的连接");
}

void MainWindow::readyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_socket);
    socketStream.setVersion(QDataStream::Qt_5_12);

    for (;;) {
        socketStream.startTransaction();
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject()) {
                    processJson(jsonDoc.object());
                }
            }
        } else {
            break;
        }
    }
}

void MainWindow::processJson(const QJsonObject &json)
{
    const QString type = json.value("type").toString();

    if (type == "loginSuccess") {
        // 登录成功
        ui->stackedWidget->setCurrentWidget(ui->chatPage_2);
        ui->loginBtn_2->setEnabled(true);
        ui->loginBtn_2->setText("登录");

        // 显示欢迎消息
        QString welcomeMsg = QString("欢迎 %1 进入聊天室！").arg(m_userName);
        ui->roomTextEdit->append(welcomeMsg);

    } else if (type == "message") {
        // 收到聊天消息
        QString sender = json.value("sender").toString();
        QString text = json.value("text").toString();
        QString timestamp = json.value("timestamp").toString();

        QString displayMsg;
        if (sender == m_userName) {
            displayMsg = QString("[%1] 我: %2").arg(timestamp).arg(text);
        } else {
            displayMsg = QString("[%1] %2: %3").arg(timestamp).arg(sender).arg(text);
        }

        ui->roomTextEdit->append(displayMsg);

    } else if (type == "userList") {
        // 更新用户列表
        ui->userList->clear();
        QJsonArray users = json.value("users").toArray();
        for (const QJsonValue &user : users) {
            ui->userList->addItem(user.toString());
        }

    } else if (type == "userJoined") {
        // 新用户加入
        QString userName = json.value("userName").toString();
        ui->roomTextEdit->append(QString("系统: %1 加入了聊天室").arg(userName));

    } else if (type == "userLeft") {
        // 用户离开
        QString userName = json.value("userName").toString();
        ui->roomTextEdit->append(QString("系统: %1 离开了聊天室").arg(userName));
    }
}

void MainWindow::on_send_clicked()
{
    QString text = ui->content->text().trimmed();
    if (text.isEmpty())
        return;

    // 构建消息JSON
    QJsonObject message;
    message["type"] = "message";
    message["text"] = text;

    sendJson(message);

    // 清空输入框
    ui->content->clear();

    // 给自己也显示消息
    QString displayMsg = QString("[%1] 我: %2")
                             .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                             .arg(text);
    ui->roomTextEdit->append(displayMsg);
}

void MainWindow::on_logoutBtn_2_clicked()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->disconnectFromHost();
    } else {
        ui->stackedWidget->setCurrentWidget(ui->loginPage_2);
    }
}

void MainWindow::sendJson(const QJsonObject &json)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState)
        return;

    QDataStream socketStream(m_socket);
    socketStream.setVersion(QDataStream::Qt_5_12);
    socketStream << QJsonDocument(json).toJson(QJsonDocument::Compact);
}
