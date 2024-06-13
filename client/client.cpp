#include "client.h"

Client::Client(QHostAddress ip, ushort port, QObject *parent)
    : QObject{parent},
    _ip(ip),
    _port(port)
{
    setupClient();
}

void Client::connectToServer()
{
    _socket->connectToHost(_ip, _port);
}

void Client::sendMessage(QString message, QString receiver)
{
    _socket->write(_chat.textMessage(message, receiver));
}

void Client::sendName(QString name)
{
    _socket->write(_chat.setNameMessage(name));
}

void Client::readyRead()
{
    auto data = _socket->readAll(); //Чтение всех данных из сокета
    _chat.loadData(data);   //Загрузка данных
    switch (_chat.type()) {
    case Chat::Text:
        emit textMessageReceived(_chat.message());
        break;
    case Chat::SetName:
        emit nameChanged(_chat.name());
        break;
    case Chat::Connection:
        emit connection(_chat.myName(), _chat.clientsName());
        break;
    case Chat::NewClient:
        emit newClientConnectedToServer(_chat.clientName());
        break;
    case Chat::ClientDisconnected:
        emit clientDisconnected(_chat.clientName());
        break;
    case Chat::ClientName:
        emit clientNameChanged(_chat.prevName(), _chat.clientName());
        break;
    default:
        break;
    }
}

void Client::setupClient()
{
    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &Client::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
}
