#include "server.h"

Server::Server(ushort port, QObject *parent)
    : QObject{parent}
{
    setupServer(port);
}

void Server::notifyOtherClients(QString prevName, QString name) //Уведомление других клиентов о смене имени клиента
{
    auto logMessage = QString("Имя клиента изменено: %1 -> %2").arg(prevName).arg(name);
    logToFile(logMessage);
    auto message = _chat.setClientNameMessage(prevName, name);
    foreach (auto cl, _clients) {
        auto clientName = cl->property("clientName").toString();
        if (clientName != name) {
            cl->write(message);
        }
    }
}

void Server::onTextForOtherClients(QString message, QString receiver, QString sender)
{
    auto logMessage = QString("Сообщение: %1. Отправитель: %2. Получатель: %3").arg(message).arg(sender).arg(receiver);
    logToFile(logMessage);
    auto msg = _chat.textMessage(message, receiver);
    if (receiver == "Broadcast") {
        foreach (auto cl, _clients) {
            auto clientName = cl->property("clientName").toString();
            if (clientName != sender) {
                cl->write(msg);
            }
        }
    } else {
        foreach (auto cl, _clients) {
            auto clientName = cl->property("clientName").toString();
            if (clientName == receiver) {
                cl->write(msg);
                return;
            }
        }
    }
}

void Server::newClientConnectionReceived()  //Подключение нового клиента
{
    auto client = _server->nextPendingConnection(); //Получение сокета нового клиента
    auto id = _clients.count() + 1;
    auto clientName = QString("Клиент (%1)").arg(id);
    client->setProperty("id", id);
    client->setProperty("clientName", clientName);
    logToFile(QString("Добавлен новый клиент: %1").arg(clientName));
    connect(client, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
    emit newClientConnected(client);
    if (id > 1) {
        auto message = _chat.setConnectionMessage(clientName, _clients.keys());
        client->write(message);

        auto newClientMessage = _chat.setNewClientMessage(clientName);
        foreach (auto cl, _clients) {
            cl->write(newClientMessage);
        }
    }
    _clients[clientName] = client;
}

void Server::onClientDisconnected() //Отключение нового клиента
{
    auto client = qobject_cast<QTcpSocket *>(sender());
    auto clientName = client->property("clientName").toString();
    logToFile(QString("Клиент отключен: %1").arg(clientName));
    _clients.remove(clientName);
    auto message = _chat.setClinetDisconnectedMessage(clientName);
    foreach (auto cl, _clients) {
        cl->write(message);
    }
    emit clientDisconnected(client);
}

void Server::logToFile(const QString &message) {
    QFile file("log.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
        file.close();
    } else {
        qDebug() << "Ошибка: невозможно открыть файл журнала для записи";
    }
}

void Server::setupServer(ushort port)
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &Server::newClientConnectionReceived);
    _server->listen(QHostAddress::Any, port);
    logToFile(QString("Сервер запущен"));
}
