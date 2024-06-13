#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::setMessage(QString message, bool isMyMessage)
{
    if(isMyMessage){
        ui->lblMessage->setAlignment(Qt::AlignRight);   //Выравнивание текста сообщения по правому краю, если сообщение принадлежит пользователю
        ui->lblTime->setAlignment(Qt::AlignRight);
    }
    ui->lblMessage->setText(message);
    ui->lblTime->setText(QTime::currentTime().toString("HH:mm"));
}
