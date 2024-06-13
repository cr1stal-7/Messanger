/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *lstMessages;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lnMessage;
    QPushButton *btnSend;
    QLineEdit *lnClientName;
    QLabel *label_3;
    QPushButton *button_connect;
    QComboBox *cmbDestination;
    QLabel *label_2;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(440, 420);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(false);
        lstMessages = new QListWidget(centralwidget);
        lstMessages->setObjectName("lstMessages");
        lstMessages->setGeometry(QRect(11, 78, 421, 271));
        lstMessages->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 350, 421, 51));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lnMessage = new QLineEdit(layoutWidget);
        lnMessage->setObjectName("lnMessage");

        gridLayout->addWidget(lnMessage, 0, 0, 1, 2);

        btnSend = new QPushButton(layoutWidget);
        btnSend->setObjectName("btnSend");
        btnSend->setEnabled(false);

        gridLayout->addWidget(btnSend, 0, 2, 1, 1);

        lnClientName = new QLineEdit(centralwidget);
        lnClientName->setObjectName("lnClientName");
        lnClientName->setGeometry(QRect(240, 12, 121, 24));
        lnClientName->setFrame(true);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 10, 61, 21));
        button_connect = new QPushButton(centralwidget);
        button_connect->setObjectName("button_connect");
        button_connect->setEnabled(false);
        button_connect->setGeometry(QRect(12, 12, 144, 24));
        cmbDestination = new QComboBox(centralwidget);
        cmbDestination->addItem(QString());
        cmbDestination->addItem(QString());
        cmbDestination->setObjectName("cmbDestination");
        cmbDestination->setGeometry(QRect(182, 51, 81, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 171, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 440, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        lnClientName->setText(QString());
        lnClientName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\262\320\276\320\265 \320\270\320\274\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "          \320\230\320\274\321\217         ", nullptr));
        button_connect->setText(QCoreApplication::translate("MainWindow", "         \320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217         ", nullptr));
        cmbDestination->setItemText(0, QCoreApplication::translate("MainWindow", "Server", nullptr));
        cmbDestination->setItemText(1, QCoreApplication::translate("MainWindow", "Broadcast", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", " \320\232\320\276\320\274\321\203 \320\276\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
