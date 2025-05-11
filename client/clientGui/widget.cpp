#include "widget.h"
#include "ui_widget.h"
//-----------------------------------------------------------------------------------------------
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
      PORT(""),
      IP_ADDRESS("")
{
    ui->setupUi(this);
    this->setWindowTitle("Chattt");
    ui->nameLED->setPlaceholderText("Enter your userName...");
    ui->inputTE->setPlaceholderText("Message...");
    ui->portLED->setPlaceholderText("Enter the server PORT...");
    ui->ipAddressLED->setPlaceholderText("Enter the server IP_ADDRESS...");
    ui->sendPBN->setEnabled(false);
    ui->inputTE->setEnabled(false);
    log( "The application is running!" );

    ui->inputTE->installEventFilter(this);   // for keyboard

    connect(&webSocketClient, &QWebSocket::connected, this, &Widget::onSocketConnected);
    connect(&webSocketClient, &QWebSocket::disconnected, this, &Widget::onSocketDisconnected);
    connect(&webSocketClient, &QWebSocket::binaryMessageReceived, this, &Widget::onBinaryMessageReceived);


}
//-----------------------------------------------------------------------------------------------
Widget::~Widget()
{
    webSocketClient.close();
    delete ui;
}

//-----------------------------------------------------------------------------------------------
void Widget::on_connectPBN_clicked()
{
    userName = ui->nameLED->text().trimmed();
    if (userName.isEmpty()) {
        log("Error: Username cannot be empty!");
    }

    IP_ADDRESS = ui->ipAddressLED->text().trimmed();

    PORT = ui->portLED->text().trimmed();

    if (IP_ADDRESS.isEmpty() || PORT.isEmpty()) {
        log("Error: IP and Port cannot be empty!");
    }

    if(!userName.isEmpty() && !IP_ADDRESS.isEmpty() && !PORT.isEmpty()){
       QString url = QString("ws://%1:%2/chat").arg(IP_ADDRESS).arg(PORT);
       connectToServer(url);
    }

}
//-----------------------------------------------------------------------------------------------
void Widget::on_sendPBN_clicked()
{
    QString message = ui->inputTE->toPlainText();

    if(message.isEmpty()) return;
    QString data = QString("%1: %2").arg(userName).arg(message);
    webSocketClient.sendTextMessage(data);
    ui->inputTE->clear();

}
//-----------------------------------------------------------------------------------------------
void Widget::onSocketConnected()
{
    log("Connected to server: " + IP_ADDRESS + ":" + PORT);
    ui->sendPBN->setEnabled(true);
    ui->inputTE->setEnabled(true);
    ui->connectPBN->setEnabled(false);
}
//-----------------------------------------------------------------------------------------------
void Widget::onSocketDisconnected()
{
    log("Disconnected from server.");
    ui->sendPBN->setEnabled(false);
    ui->inputTE->setEnabled(false);
    ui->connectPBN->setEnabled(true);
}

void Widget::onBinaryMessageReceived(const QByteArray &message)
{
    log(QString::fromUtf8(message));
}
//-----------------------------------------------------------------------------------------------
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    // проверяем такое ли событие вообще
    if (obj == ui->inputTE && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        // Проверяем, была ли нажата клавиша Enter (без Shift)
        if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) &&
            !(keyEvent->modifiers() & Qt::ControlModifier)) {
            on_sendPBN_clicked(); // Вызываем метод отправки сообщения
            return true; // Событие обработано
        }

        if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) &&
            (keyEvent->modifiers() & Qt::ControlModifier)) {
            // Вставляем перенос строки
            ui->inputTE->insertPlainText("\n");
            return true; // Событие обработано
        }
    }
    return QWidget::eventFilter(obj, event);
}
//-----------------------------------------------------------------------------------------------
void Widget::log(const QString &s)
{
     QString m;
     m = QTime::currentTime().toString("hh:mm");
     m += " - ";
     m += s;
     ui->logTE->append(m);
     // qDebug() << m;
}
//-----------------------------------------------------------------------------------------------
void Widget::connectToServer(const QString &url)
{
    webSocketClient.open(QUrl(url));
}
//-----------------------------------------------------------------------------------------------
