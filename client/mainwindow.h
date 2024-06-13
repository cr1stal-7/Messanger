#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "client.h"

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
    void on_btnSend_clicked();  //Кнопка отправить
    void dataReceived(QString message); //Получение данных
    void on_lnClientName_editingFinished(); //Завершение редактирования имени клиента
    void onConnection(QString myName, QStringList clientsName);
    void onNewClientConnectedToServer(QString clienName);   //Добавление нового клиента
    void onClientNameChanged(QString prevName, QString clientName); //Изменение имени клиента
    void onClientDisconnected(QString clientName);
    void on_button_connect_clicked();   //Кнопка подключиться
    void on_lnMessage_returnPressed();

private:
    Ui::MainWindow *ui;
    Client *_client;
    void setupClient();
};
#endif // MAINWINDOW_H
