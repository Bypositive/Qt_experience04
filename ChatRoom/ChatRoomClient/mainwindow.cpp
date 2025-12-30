#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage_2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage_2);
}


void MainWindow::on_send_clicked()
{

}


void MainWindow::on_logoutBtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage_2);

}

