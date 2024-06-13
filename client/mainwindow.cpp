#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:/Users/5221/Desktop/Kursach/back.jpg"); //Установка фона
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui->centralwidget->setEnabled(true);
    ui->button_connect->setEnabled(true);
    ui->lnClientName->setEnabled(false);
    ui->cmbDestination->setEnabled(false);
    ui->label_2->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->lstMessages->setEnabled(false);
    ui->lstMessages->setPalette(palette);
    ui->lnMessage->setEnabled(false);
    ui->btnSend->setEnabled(false);
    setupClient();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupClient()
{
    _client = new Client();
    connect(_client , &Client::connected, [this](){
        ui->button_connect->setEnabled(false);
        ui->lnClientName->setEnabled(true);
        ui->cmbDestination->setEnabled(true);
        ui->label_2->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->lstMessages->setEnabled(true);
        ui->lnMessage->setEnabled(true);
        ui->btnSend->setEnabled(true);
    });
    connect(_client, &Client::disconnected, [this](){
        ui->button_connect->setEnabled(true);
        ui->lnClientName->setEnabled(false);
        ui->cmbDestination->setEnabled(false);
        ui->label_2->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->lstMessages->setEnabled(false);
        ui->lnMessage->setEnabled(false);
        ui->btnSend->setEnabled(false);
    });
    connect(_client, &Client::textMessageReceived, this, &MainWindow::dataReceived);    //Обработка полученных сообщений
    connect(_client, &Client::connection, this, &MainWindow::onConnection);     //Обработка подтверждения соединения
    connect(_client, &Client::newClientConnectedToServer, this, &MainWindow::onNewClientConnectedToServer); //Обработка подключения нового клиента
    connect(_client, &Client::clientDisconnected, this, &MainWindow::onClientDisconnected);    //Обработка отключения клиента
    connect(_client, &Client::clientNameChanged, this, &MainWindow::onClientNameChanged);   //Обработка изменения имени клиента
}

void MainWindow::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed(); //Получение текста сообщения
    if(message != "")
    {
        _client->sendMessage(message, ui->cmbDestination->currentText());   //Отправка сообщения выбранному получателю
        auto chatWidget = new ChatWidget();
        chatWidget->setMessage(message, true);
        auto listWidgetItem = new QListWidgetItem();
        listWidgetItem->setSizeHint(QSize(0, 65));
        ui->lstMessages->addItem(listWidgetItem);
        ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Cтрока не может быть пустой");
    }
    ui->lnMessage->clear();
}

void MainWindow::dataReceived(QString message)
{
    auto chatWidget = new ChatWidget();
    chatWidget->setMessage(message);    //Установка полученного сообщения в виджет
    auto listWidgetItem = new QListWidgetItem();
    listWidgetItem->setSizeHint(QSize(0, 65));
    ui->lstMessages->addItem(listWidgetItem);   //Добавление элемента списка в виджет
    ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
}

void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);    //Отправка имени на сервер
    ui->lstMessages->clear();
}

void MainWindow::onConnection(QString myName, QStringList clientsName)
{
    ui->cmbDestination->clear();
    clientsName.prepend("Broadcast");
    clientsName.prepend("Server");
    foreach (auto client, clientsName) {    //Добавление имен всех клиентов в список получателей
        ui->cmbDestination->addItem(client);
    }
    setWindowTitle(myName);
}

void MainWindow::onNewClientConnectedToServer(QString clienName)
{
    ui->cmbDestination->addItem(clienName); //Добавление имени нового клиента в список получателей
}

void MainWindow::onClientNameChanged(QString prevName, QString clientName)
{
    for (int i = 0; i < ui->cmbDestination->count(); ++i) { // Поиск и замена имени клиента в списке получателей
        if (ui->cmbDestination->itemText(i) == prevName) {
            ui->cmbDestination->setItemText(i, clientName);
            return;
        }
    }
}

void MainWindow::onClientDisconnected(QString clientName)
{
    for (int i = 0; i < ui->cmbDestination->count(); ++i) { //Поиск и удаление имени клиента из списка получателей
        if (ui->cmbDestination->itemText(i) == clientName) {
            ui->cmbDestination->removeItem(i);
            return;
        }
    }
}

void MainWindow::on_button_connect_clicked()
{
    _client->connectToServer();
}

void MainWindow::on_lnMessage_returnPressed()
{
    auto message = ui->lnMessage->text().trimmed();
    if(message != "")
    {
        _client->sendMessage(message, ui->cmbDestination->currentText());
        auto chatWidget = new ChatWidget();
        chatWidget->setMessage(message, true);
        auto listWidgetItem = new QListWidgetItem();
        listWidgetItem->setSizeHint(QSize(0, 65));
        ui->lstMessages->addItem(listWidgetItem);
        ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Cтрока не может быть пустой");
    }
    ui->lnMessage->clear();
}

