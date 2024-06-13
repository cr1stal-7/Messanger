#ifndef CLIENT_H
#define CLIENT_H

#include "chat.h"
#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    void connectToServer(); //Подключение к серверу по заданному ip-адресу и порту
    void sendMessage(QString message, QString receiver);    //Отправка текстового сообщения серверу через сокет
    void sendName(QString name);    //Отправка серверу сообщения об изменении имени

signals:
    void connected();       //Подключение к серверу
    void disconnected();    //Отключение от сервера
    void textMessageReceived(QString message);  //Отправка сигнала о получении текстового сообщения
    void nameChanged(QString name); //Отправка сигнала об изменении имени
    void connection(QString myName, QStringList clientsName); //Отправка сигнала об успешном подключении
    void newClientConnectedToServer(QString clienName); //Отправка сигнала о подключении нового клиента
    void clientNameChanged(QString prevName, QString clientName);   //Отправка сигнала об изменении имени клиента
    void clientDisconnected(QString clientName);    //Отправка сигнала об отключении клиента

private slots:
    void readyRead(); //Обработка данных

private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    Chat _chat;
    void setupClient();
};

#endif // CLIENT_H
