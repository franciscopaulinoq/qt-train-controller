#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ClientWindow;
}
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_btnTrainOn_clicked();
    void on_btnTrainOff_clicked();
    void on_sliderSpeed_valueChanged(int value);


    // socket events
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError);

private:
    Ui::ClientWindow *ui;
    QTcpSocket *socket;

    void log(const QString &msg);
    void sendCommand(const QString &cmd);
    void sendJson(const QJsonObject &jsonObj);
};

#endif // CLIENTWINDOW_H
