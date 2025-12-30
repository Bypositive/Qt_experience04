#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QNetworkInterface>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chatServer = new ChatServer(this);

    connect(m_chatServer, &ChatServer::logMessage, this, &MainWindow::logMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartAndStopBtn_clicked()
{
    if(m_chatServer->isListening()){
        m_chatServer->stopServer();
        ui->StartAndStopBtn->setText("启动服务器");
        logMessage("============================================");
        logMessage("服务器已停用");
        logMessage("============================================\n");
    }else{
        // 获取本机IP地址
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        for (const QHostAddress &address : ipAddressesList) {
            if (address != QHostAddress::LocalHost && address.toIPv4Address()) {
                if (address.toString().startsWith("192.168.") ||
                    address.toString().startsWith("10.") ||
                    address.toString().startsWith("172.")) {
                    ipAddress = address.toString();
                    break;
                }
            }
        }
        if (ipAddress.isEmpty()) {
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        }

        if(!m_chatServer->listen(QHostAddress::Any, 1967)){
            QMessageBox::critical(this, "错误", "无法启动服务器");
            return;
        }

        ui->StartAndStopBtn->setText("停用服务器");

        // 显示详细的服务器启动信息
        logMessage("============================================");
        logMessage("服务器已成功启动");
        logMessage("============================================");
        logMessage(QString("服务器时间：%1").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
        logMessage(QString("服务器IP：%1").arg(ipAddress));
        logMessage(QString("服务器端口：%1").arg(m_chatServer->serverPort()));
        logMessage(QString("监听地址：任意地址 (0.0.0.0)"));
        logMessage("============================================\n");
        logMessage("等待客户端连接...\n");
    }
}

void MainWindow::logMessage(const QString &msg)
{
    ui->logEdit->appendPlainText(msg);
}
