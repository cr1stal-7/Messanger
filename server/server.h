#ifndef SERVER_H
#define SERVER_H

#include "chat.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTime>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(ushort port = 4500, QObject *parent = nullptr);
    void notifyOtherClients(QString prevName, QString name);    //Уведомление других клиентов об изменении имени

public slots:
    void onTextForOtherClients(QString message, QString receiver, QString sender); //Обработка сообщения для других клиентов

signals:
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket *client);

private slots:
    void newClientConnectionReceived();
    void onClientDisconnected();

private:
    QTcpServer *_server;
    QMap<QString, QTcpSocket *> _clients;
    Chat _chat;
    void setupServer(ushort port);
    void logToFile(const QString &message); //Запись логов
};

#endif // SERVER_H
