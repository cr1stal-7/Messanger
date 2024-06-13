#ifndef CHAT_H
#define CHAT_H

#include <QByteArray>
#include <QString>
#include <QStringList>
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
    void loadData(QByteArray data); //Загрузка данных
    //Геттеры для различных данных
    const QString &message() const;
    const QString &name() const;
    MessageType type() const;
    QString receiver() const;
    const QString &clientName() const;
    const QString &prevName() const;
    const QStringList &clientsName() const;
    const QString &myName() const;

private:
    QByteArray getData(MessageType type, QString data);
    MessageType _type;
    QString _message;
    QString _name;
    QString _receiver;
    QString _clientName;
    QString _prevName;
    QStringList _clientsName;
    QString _myName;
    QByteArray Data;

};

#endif // CHAT_H
