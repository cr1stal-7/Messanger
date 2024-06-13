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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tbClientsChat;
    QListWidget *lstClients;
    QPushButton *btnDisconnectAll;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(659, 296);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tbClientsChat = new QTabWidget(centralwidget);
        tbClientsChat->setObjectName("tbClientsChat");
        tbClientsChat->setGeometry(QRect(20, 40, 371, 221));
        tbClientsChat->setTabsClosable(true);
        lstClients = new QListWidget(centralwidget);
        lstClients->setObjectName("lstClients");
        lstClients->setGeometry(QRect(400, 40, 241, 191));
        btnDisconnectAll = new QPushButton(centralwidget);
        btnDisconnectAll->setObjectName("btnDisconnectAll");
        btnDisconnectAll->setGeometry(QRect(440, 240, 151, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(440, 10, 161, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 10, 31, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 659, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        btnDisconnectAll->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\262\321\201\320\265\321\205 \320\272\320\273\320\270\320\265\320\275\321\202\320\276\320\262", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \320\272\320\273\320\270\320\265\320\275\321\202\321\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
