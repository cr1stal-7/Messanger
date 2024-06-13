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

QByteArray Chat::setClientNameMessage(QString prevName, QString name)
{
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << ClientName << prevName << name;
    return Data;
}

QByteArray Chat::setConnectionMessage(QString clientName, QStringList otherClients)
{
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << Connection << clientName << otherClients;
    return Data;
}

QByteArray Chat::setNewClientMessage(QString clientName)
{
    return getData(NewClient, clientName);
}

QByteArray Chat::setClinetDisconnectedMessage(QString clientName)
{
    return getData(ClientDisconnected, clientName);
}

void Chat::loadData(QByteArray Data)
{
    QDataStream in(&Data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_7);
    in >> _type;    //Чтение типа сообщения
    switch (_type) {
    case Text:
        in >> _receiver >> _message;    //Чтение получателя и текста сообщения
        break;
    case SetName:
        in >> _name;    //Чтение имени
        break;
    default:
        break;
    }
}

QByteArray Chat::getData(MessageType type, QString data)
{
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_7);
    out << type << data;    //Запись типа сообщения и данных
    return Data;
}

const QString &Chat::receiver() const
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
