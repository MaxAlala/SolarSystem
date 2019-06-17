/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QProgressBar *pbar;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *start;
    QPushButton *portrait;
    QPushButton *portrait_2;
    QPushButton *pushButton;
    QLabel *finish_label;
    QPlainTextEdit *log;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSlider *sliderdown;
    QSlider *slidertop;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *XYregime;
    QPushButton *Xregime;
    QPushButton *Yregime;
    QPushButton *two;
    QPushButton *full;
    QPushButton *pushButton_2;
    QPushButton *clear;
    QLineEdit *inputZ;
    QPushButton *sendZ;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1142, 623);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #CFCFCF;"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 491, 481));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("  background-color: #f0a105;"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 521, 21));
        label_2->setStyleSheet(QString::fromUtf8("color"));
        pbar = new QProgressBar(centralWidget);
        pbar->setObjectName(QString::fromUtf8("pbar"));
        pbar->setGeometry(QRect(30, 470, 451, 23));
        pbar->setStyleSheet(QString::fromUtf8("color:blue;"));
        pbar->setValue(24);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 510, 411, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        start = new QPushButton(layoutWidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(start);

        portrait = new QPushButton(layoutWidget);
        portrait->setObjectName(QString::fromUtf8("portrait"));
        portrait->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(portrait);

        portrait_2 = new QPushButton(layoutWidget);
        portrait_2->setObjectName(QString::fromUtf8("portrait_2"));
        portrait_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(portrait_2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton);

        finish_label = new QLabel(centralWidget);
        finish_label->setObjectName(QString::fromUtf8("finish_label"));
        finish_label->setGeometry(QRect(190, 470, 111, 20));
        finish_label->setStyleSheet(QString::fromUtf8("QLabel {background: transparent\n"
"\n"
"\n"
"}"));
        log = new QPlainTextEdit(centralWidget);
        log->setObjectName(QString::fromUtf8("log"));
        log->setGeometry(QRect(510, 20, 621, 481));
        log->setAutoFillBackground(true);
        log->setReadOnly(true);
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 550, 151, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        sliderdown = new QSlider(layoutWidget1);
        sliderdown->setObjectName(QString::fromUtf8("sliderdown"));
        sliderdown->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sliderdown);

        slidertop = new QSlider(layoutWidget1);
        slidertop->setObjectName(QString::fromUtf8("slidertop"));
        slidertop->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slidertop);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(184, 550, 495, 34));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 5);
        XYregime = new QPushButton(layoutWidget2);
        XYregime->setObjectName(QString::fromUtf8("XYregime"));

        horizontalLayout_4->addWidget(XYregime);

        Xregime = new QPushButton(layoutWidget2);
        Xregime->setObjectName(QString::fromUtf8("Xregime"));

        horizontalLayout_4->addWidget(Xregime);

        Yregime = new QPushButton(layoutWidget2);
        Yregime->setObjectName(QString::fromUtf8("Yregime"));

        horizontalLayout_4->addWidget(Yregime);

        two = new QPushButton(layoutWidget2);
        two->setObjectName(QString::fromUtf8("two"));

        horizontalLayout_4->addWidget(two);

        full = new QPushButton(layoutWidget2);
        full->setObjectName(QString::fromUtf8("full"));

        horizontalLayout_4->addWidget(full);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 510, 71, 31));
        clear = new QPushButton(centralWidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(1090, 500, 41, 31));
        inputZ = new QLineEdit(centralWidget);
        inputZ->setObjectName(QString::fromUtf8("inputZ"));
        inputZ->setGeometry(QRect(510, 511, 113, 31));
        sendZ = new QPushButton(centralWidget);
        sendZ->setObjectName(QString::fromUtf8("sendZ"));
        sendZ->setGeometry(QRect(630, 510, 51, 31));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        start->setText(QApplication::translate("MainWindow", "createServer", nullptr));
        portrait->setText(QApplication::translate("MainWindow", "startCam", nullptr));
        portrait_2->setText(QApplication::translate("MainWindow", "downloadImg", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "exit", nullptr));
        finish_label->setText(QString());
        XYregime->setText(QApplication::translate("MainWindow", "xy", nullptr));
        Xregime->setText(QApplication::translate("MainWindow", "x", nullptr));
        Yregime->setText(QApplication::translate("MainWindow", "y", nullptr));
        two->setText(QApplication::translate("MainWindow", "two", nullptr));
        full->setText(QApplication::translate("MainWindow", "full", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "rebootS", nullptr));
        clear->setText(QApplication::translate("MainWindow", "clear", nullptr));
        sendZ->setText(QApplication::translate("MainWindow", "sendZ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
