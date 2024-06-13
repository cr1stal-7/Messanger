#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "clientchatwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newClientConnected(QTcpSocket *client);    //Подключение клиента
    void clientDisconnected(QTcpSocket *client);    //Отключение клиента
    void setClientName(QString prevName, QString name); //Изменение имени клиента
    void on_tbClientsChat_tabCloseRequested(int index); //Закрытие вкладки чата клиента
    void on_btnDisconnectAll_clicked(); //Отключение всех клиентов

private:
    Ui::MainWindow *ui;
    Server *_server;
    void setupServer();
    void logToFile(const QString &message); //Запись логов
};
#endif // MAINWINDOW_H
