#include "client.h"

Client::Client(QHostAddress ip, ushort port, QObject *parent)
    : QObject{parent},
      _ip(ip),
      _port(port)
{
    _socket = new QTcpSocket(this);
    setupClient();
}

Client::Client(QTcpSocket *client, QObject *parent)
    : QObject{parent},
    _socket(client)
{
    setupClient();
}

void Client::connectToServer()
{
    _socket->connectToHost(_ip, _port); //Установка соединения с сервером
}

void Client::disconnectFromHost()
{
    _socket->disconnectFromHost();
}

void Client::sendMessage(QString message)   //Отправка текстового сообщения
{
    _socket->write(_chat.textMessage(QString("Сервер: %1").arg(message), name()));  //Отправка сообщения через сокет
}

void Client::sendName(QString name)     //Отправка имени клиента
{
    _socket->write(_chat.setNameMessage(name));
}

QString Client::name() const        //Получение имени клиента
{
    auto id = _socket->property("id").toInt();
    auto name = _chat.name().length() > 0 ? _chat.name() : QString("Клиент (%1)").arg(id);
    return name;
}

void Client::readyRead()    //Обработка данных
{
    auto data = _socket->readAll();
    _chat.loadData(data);
    switch (_chat.type()) {
    case Chat::Text:
        emit textMessageReceived(_chat.message(), _chat.receiver());
        break;
    case Chat::SetName:{
        auto prevName = _socket->property("clientName").toString();
        _socket->setProperty("clientName", _chat.name());
        emit nameChanged(prevName, _chat.name());
        break;
    }
    default:
        break;
    }
}

void Client::setupClient()
{
    connect(_socket, &QTcpSocket::connected, this, &Client::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
}

