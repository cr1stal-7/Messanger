#include "chat.h"

Chat::Chat()
{

}

QByteArray Chat::textMessage(QString message, QString receiver)
{
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << Text << receiver << message;
    return Data;
}

QByteArray Chat::setNameMessage(QString name)
{
    return getData(SetName, name);
}

void Chat::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_7);
    in >> _type;    //Считывание типа сообщения
    switch (_type) {
    case Text:
        in >> _receiver >> _message;
        break;
    case SetName:
        in >> _name;
        break;
    case ClientName:
        in >> _prevName >> _clientName;
        break;
    case NewClient:
    case ClientDisconnected:
        in >> _clientName;
        break;
    case Connection:
        in >> _myName >> _clientsName;
        break;
    default:
        break;
    }
}

QByteArray Chat::getData(MessageType type, QString data)
{
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << type << data;    //Записывается тип сообщения и данные
    return Data;
}

const QString &Chat::myName() const
{
    return _myName;
}

const QStringList &Chat::clientsName() const
{
    return _clientsName;
}

const QString &Chat::prevName() const
{
    return _prevName;
}

const QString &Chat::clientName() const
{
    return _clientName;
}

QString Chat::receiver() const
{
    return _receiver;
}

Chat::MessageType Chat::type() const
{
    return _type;
}

const QString &Chat::name() const
{
    return _name;
}

const QString &Chat::message() const
{
    return _message;
}
