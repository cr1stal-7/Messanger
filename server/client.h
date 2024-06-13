#ifndef CLIENT_H
#define CLIENT_H

#include "chat.h"
#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QHostAddress ip = QHostAddress::Any, ushort port = 4500, QObject *parent = nullptr);
    explicit Client(QTcpSocket *client, QObject *parent = nullptr);
    void connectToServer();     //Подключения к серверу
    void disconnectFromHost();  //Отключения от сервера
    void sendMessage(QString message);  //Отправки текстового сообщения
    void sendName(QString name);    //Отправки имени клиента
    QString name() const;   //Получения имени клиента

signals:
    void connected();       //Подключение к серверу
    void disconnected();    //Отключение от сервера
    void textMessageReceived(const QString message, QString receiver);  //Получение текстового сообщения
    void nameChanged(QString prevName, QString name);   //Изменение имени клиента

private slots:
    void readyRead();   //Обработка данных

private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    Chat _chat;
    void setupClient();
};

#endif // CLIENT_H
