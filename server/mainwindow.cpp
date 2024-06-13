#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:/Users/5221/Desktop/Kursach/back.jpg");    //Установка фона
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setupServer();
}

MainWindow::~MainWindow()
{
    logToFile(QString("Сервер выключен"));
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket *client) //Подключение нового клиента
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("Добавлен новый клиент: %1").arg(id));  //Добавление записи о новом клиенте
    auto chatWidget= new ClientChatWidget(client, ui->tbClientsChat);   //Создание виджета чата нового клиента
    ui->tbClientsChat->addTab(chatWidget, QString("Клиент (%1)").arg(id));  //Добавление вкладки для нового виджета чата
    connect(chatWidget, &ClientChatWidget::clientNameChanged, this, &MainWindow::setClientName);    //Изменение имени клиента
    connect(ui->btnDisconnectAll, &QPushButton::clicked, this, &MainWindow::on_btnDisconnectAll_clicked);   //Отключении всех клиентов
    connect(chatWidget, &ClientChatWidget::textForOtherClients, _server, &Server::onTextForOtherClients);   //Сообщение для других клиентов
}

void MainWindow::clientDisconnected(QTcpSocket *client) //Отключение клиента
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("Клиент отключен: %1").arg(id));
}

void MainWindow::setClientName(QString prevName, QString name)  //Изменение имени клиента
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tbClientsChat->indexOf(widget);
    ui->tbClientsChat->setTabText(index, name); //Установка нового имени клиента
    _server->notifyOtherClients(prevName, name);//Уведомление других клиентов об изменении имени
}

void MainWindow::setupServer()
{
    _server = new Server();
    connect(_server, &Server::newClientConnected, this, &MainWindow::newClientConnected);
    connect(_server, &Server::clientDisconnected, this, &MainWindow::clientDisconnected);

}

void MainWindow::logToFile(const QString &message) {
    QFile file("log.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
        file.close();
    } else {
        qDebug() << "Ошибка: невозможно открыть файл журнала для записи";
    }
}

void MainWindow::on_tbClientsChat_tabCloseRequested(int index)  //Закрытие вкладки чата клиента
{
    auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbClientsChat->widget(index));
    chatWidget->disconnect();
    ui->tbClientsChat->removeTab(index);
}

void MainWindow::on_btnDisconnectAll_clicked()  //Отключение всех клиентов
{
    for (int i = 0; i < ui->tbClientsChat->count(); ++i) {
        auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbClientsChat->widget(i));
        if(chatWidget) {
            chatWidget->disconnect();
            ui->tbClientsChat->removeTab(i);
        }
    }
}

