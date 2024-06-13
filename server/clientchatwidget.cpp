#include "ClientChatWidget.h"
#include "ui_ClientChatWidget.h"

ClientChatWidget::ClientChatWidget(QTcpSocket *client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientChatWidget)
{
    ui->setupUi(this);
    _client = new Client(client, this);
    connect(_client, &Client::disconnected, this, &ClientChatWidget::clientDisconnected);
    connect(_client, &Client::textMessageReceived, this, &ClientChatWidget::textMessageReceived);
    connect(_client, &Client::nameChanged, this, &ClientChatWidget::onClientNameChanged);
}

void ClientChatWidget::disconnect()
{
    _client->disconnectFromHost();  //Отключение клиента от сервера
}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSendMessage->setEnabled(false);  //Отключение виджета отправки сообщения
}

void ClientChatWidget::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed(); //Получение текста сообщения
    if(message != "")
    {
        _client->sendMessage(message);  //Отправка сообщения
        logToFile(QString("Сообщение: %1. Отправитель: Сервер. Получатель: %2").arg(message).arg(_client->name()));
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Cтрока не может быть пустой");
    }
    ui->lnMessage->clear();
    ui->lstMessages->addItem(message);  //Добавление сообщения в список сообщений
}

void ClientChatWidget::on_lnMessage_returnPressed()
{
    auto message = ui->lnMessage->text().trimmed(); //Получение текста сообщения
    if(message != "")
    {
        _client->sendMessage(message);  //Отправка сообщения
        logToFile(QString("Сообщение: %1. Отправитель: Сервер. Получатель: %2").arg(message).arg(_client->name()));
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Cтрока не может быть пустой");
    }
    ui->lnMessage->clear();
    ui->lstMessages->addItem(message);
}

void ClientChatWidget::textMessageReceived(QString message, QString receiver)
{
    if (receiver == "Server") {
        ui->lstMessages->addItem(message);
        auto logMessage = QString("Сообщение: %1. Отправитель: %2. Получатель: Сервер").arg(message).arg(_client->name());
        logToFile(logMessage);
    }
    if (receiver == "Broadcast")
    {
        ui->lstMessages->addItem(message);
        emit textForOtherClients(message, receiver, _client->name());
    }
    if(receiver != "Server" && receiver != "Broadcast"){
        emit textForOtherClients(message, receiver, _client->name());
    }
}

void ClientChatWidget::onClientNameChanged(QString prevName, QString name)
{
    emit clientNameChanged(prevName, name);
}

void ClientChatWidget::logToFile(const QString &message) {
    QFile file("log.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
        file.close();
    } else {
        qDebug() << "Ошибка: невозможно открыть файл журнала для записи";
    }
}
