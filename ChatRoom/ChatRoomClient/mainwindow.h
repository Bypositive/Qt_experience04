#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void processJson(const QJsonObject &json);

private slots:
    void on_loginBtn_2_clicked();
    void on_send_clicked();
    void on_logoutBtn_2_clicked();

    // 网络相关槽函数
    void connected();
    void disconnected();
    void readyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
    QString m_userName;

    void setupConnections();
    void sendJson(const QJsonObject &json);
};

#endif // MAINWINDOW_H
