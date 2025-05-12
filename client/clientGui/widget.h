#ifndef WIDGET_H
#define WIDGET_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QTime>
#include <QGridLayout>
#include <QKeyEvent>  // for enter
#include <QtWebSockets/QWebSocket>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_connectPBN_clicked();
    void on_sendPBN_clicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onBinaryMessageReceived(const QByteArray &message);


protected:
    bool eventFilter(QObject* obj, QEvent* event) override;   // Enter

private:
    Ui::Widget *ui;
    QString              userName;
    QString                  PORT;
    QString            IP_ADDRESS;
    QWebSocket    webSocketClient;

    void    log(const QString &s);
    void    connectToServer(const QString& url);
};
#endif // WIDGET_H
