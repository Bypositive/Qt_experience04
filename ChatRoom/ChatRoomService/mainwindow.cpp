#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartAndStopBtn_clicked()
{
    static bool started=false;
    if(started){
        ui->StartAndStopBtn->setText("停用服务器");
        logMessage("服务器已启动");
    }else{
        ui->StartAndStopBtn->setText("启动服务器");
        logMessage("服务器已停用");
    }
    started=!started;
}

void MainWindow::logMessage(const QString &msg)
{
    ui->logEdit->appendPlainText(msg);

}

