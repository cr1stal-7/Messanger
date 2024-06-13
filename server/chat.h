#ifndef CHAT_H
#define CHAT_H

#include <QByteArray>
#include <QString>
#include <QFileInfo>
#include <QIODevice>

class Chat
{
public:
    enum MessageType{   //Перечисление типов сообщений
        Text,           //Текстовое сообщение
        SetName,        //Сообщение для установки имени
        ClientName,     //Имя клиента
        Connection,     //Подтверждение подключения
        NewClient,      //Новый клиент
        ClientDisconnected  //Отключение
    };
    Chat();
    //Создание различных типов  сообщений
    QByteArray textMessage(QString message, QString receiver);
    QByteArray setNameMessage(QString name);
    QByteArray setClientNameMessage(QString prevName, QString name);
    QByteArray setConnectionMessage(QString clientName, QStringList otherClients);
    QByteArray setNewClientMessage(QString clientName);
    QByteArray setClinetDisconnectedMessage(QString clientName);
    void loadData(QByteArray data); //Загрузка данных
    //Геттеры для различных данных
    const QString &message() const;
    const QString &name() const;
    MessageType type() const;
    const QString &receiver() const;

private:
    QByteArray getData(MessageType type, QString data);
    MessageType _type;
    QString _message;
    QString _name;
    QString _receiver;
    QByteArray Data;

};

#endif // CHAT_H
