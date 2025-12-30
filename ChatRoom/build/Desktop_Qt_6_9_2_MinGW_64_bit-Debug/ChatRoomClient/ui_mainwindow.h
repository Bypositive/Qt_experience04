/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *chatPage_2;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QTextEdit *roomTextEdit;
    QListWidget *userList;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *content;
    QPushButton *send;
    QPushButton *logoutBtn_2;
    QWidget *loginPage_2;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *serviceEdit_2;
    QLineEdit *nameEdit_2;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *loginBtn_2;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(701, 468);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(233, 237, 162, 255), stop:0.549811 rgba(235, 204, 106, 255), stop:1 rgba(255, 180, 94, 255));"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\255\227\351\255\202\347\231\275\351\270\275\345\244\251\350\241\214\344\275\223")});
        font.setPointSize(29);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        chatPage_2 = new QWidget();
        chatPage_2->setObjectName("chatPage_2");
        gridLayout_5 = new QGridLayout(chatPage_2);
        gridLayout_5->setObjectName("gridLayout_5");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        roomTextEdit = new QTextEdit(chatPage_2);
        roomTextEdit->setObjectName("roomTextEdit");
        roomTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(roomTextEdit);

        userList = new QListWidget(chatPage_2);
        userList->setObjectName("userList");
        userList->setMaximumSize(QSize(120, 16777215));
        userList->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(userList);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        content = new QLineEdit(chatPage_2);
        content->setObjectName("content");
        content->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(content);

        send = new QPushButton(chatPage_2);
        send->setObjectName("send");
        send->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout_7->addWidget(send);

        logoutBtn_2 = new QPushButton(chatPage_2);
        logoutBtn_2->setObjectName("logoutBtn_2");
        logoutBtn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_7->addWidget(logoutBtn_2);


        verticalLayout_5->addLayout(horizontalLayout_7);


        gridLayout_5->addLayout(verticalLayout_5, 0, 0, 1, 1);

        stackedWidget->addWidget(chatPage_2);
        loginPage_2 = new QWidget();
        loginPage_2->setObjectName("loginPage_2");
        gridLayout_6 = new QGridLayout(loginPage_2);
        gridLayout_6->setObjectName("gridLayout_6");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalSpacer_4 = new QSpacerItem(19, 124, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_7 = new QSpacerItem(81, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_4 = new QLabel(loginPage_2);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_4->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_6->addWidget(label_4);

        label_5 = new QLabel(loginPage_2);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(13);
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        label_5->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_6->addWidget(label_5);


        horizontalLayout_8->addLayout(verticalLayout_6);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        serviceEdit_2 = new QLineEdit(loginPage_2);
        serviceEdit_2->setObjectName("serviceEdit_2");
        sizePolicy.setHeightForWidth(serviceEdit_2->sizePolicy().hasHeightForWidth());
        serviceEdit_2->setSizePolicy(sizePolicy);
        serviceEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_8->addWidget(serviceEdit_2);

        nameEdit_2 = new QLineEdit(loginPage_2);
        nameEdit_2->setObjectName("nameEdit_2");
        sizePolicy.setHeightForWidth(nameEdit_2->sizePolicy().hasHeightForWidth());
        nameEdit_2->setSizePolicy(sizePolicy);
        nameEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_8->addWidget(nameEdit_2);


        horizontalLayout_8->addLayout(verticalLayout_8);


        horizontalLayout_9->addLayout(horizontalLayout_8);

        horizontalSpacer_12 = new QSpacerItem(81, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_12);


        verticalLayout_7->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        horizontalSpacer_9 = new QSpacerItem(130, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        loginBtn_2 = new QPushButton(loginPage_2);
        loginBtn_2->setObjectName("loginBtn_2");
        loginBtn_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"));

        horizontalLayout_10->addWidget(loginBtn_2);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);


        verticalLayout_7->addLayout(horizontalLayout_10);

        verticalSpacer_6 = new QSpacerItem(35, 88, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout_7->addItem(verticalSpacer_6);


        gridLayout_6->addLayout(verticalLayout_7, 0, 0, 1, 1);

        stackedWidget->addWidget(loginPage_2);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\227\240\346\236\201\345\223\245\347\225\205\350\260\210\350\201\212\345\244\251\345\256\244", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\227\240\346\236\201\345\223\245\347\225\205\350\260\210\350\201\212\345\244\251\345\256\244", nullptr));
        send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutBtn_2->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
        loginBtn_2->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
