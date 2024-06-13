/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblMessage;
    QLabel *lblTime;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName("ChatWidget");
        ChatWidget->resize(421, 175);
        verticalLayout = new QVBoxLayout(ChatWidget);
        verticalLayout->setObjectName("verticalLayout");
        lblMessage = new QLabel(ChatWidget);
        lblMessage->setObjectName("lblMessage");

        verticalLayout->addWidget(lblMessage);

        lblTime = new QLabel(ChatWidget);
        lblTime->setObjectName("lblTime");

        verticalLayout->addWidget(lblTime);


        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QCoreApplication::translate("ChatWidget", "Form", nullptr));
        lblMessage->setText(QCoreApplication::translate("ChatWidget", "TextLabel", nullptr));
        lblTime->setText(QCoreApplication::translate("ChatWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
