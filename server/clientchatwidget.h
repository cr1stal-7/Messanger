#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "client.h"
#include <QTcpSocket>
#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFile>
#include <QTime>

namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *cleint, QWidget *parent = nullptr);
    void disconnect();
    ~ClientChatWidget();

private slots:
    void clientDisconnected();
    void on_btnSend_clicked();
    void textMessageReceived(QString message, QString receiver);
    void onClientNameChanged(QString prevName, QString name);
    void on_lnMessage_returnPressed();

signals:
    void clientNameChanged(QString prevName, QString name);
    void textForOtherClients(QString message, QString receiver, QString sender);

private:
    Ui::ClientChatWidget *ui;
    Client *_client;
    void logToFile(const QString &message); //Запись логов
};

#endif // CLIENTCHATWIDGET_H
