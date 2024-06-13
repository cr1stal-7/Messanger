#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTime>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    void setMessage(QString message, bool isMyMessage = false); //Отображение сообщения

private:
    Ui::ChatWidget *ui;
};

#endif // CHATWIDGET_H
