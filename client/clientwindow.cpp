#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QTcpSocket>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
    , socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // connect socket signals
    connect(socket, &QTcpSocket::connected, this, &ClientWindow::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &ClientWindow::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientWindow::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &ClientWindow::onError);

    socket->connectToHost("127.0.0.1", 1234);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

// ---------------------------
// Helper functions
// ---------------------------
void ClientWindow::log(const QString &msg)
{
    qDebug() << msg;
}

void ClientWindow::sendCommand(const QString &cmd)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(cmd.toUtf8() + "\n");
        socket->flush();
        log("[CLIENT] " + cmd);
    } else {
        log("⚠ Não conectado ao servidor!");
    }
}

// ---------------------------
// Buttons
// ---------------------------

void ClientWindow::on_btnTrainOn_clicked()
{
    int id = ui->lineTrainId->text().toInt();
    int speed = ui->sliderSpeed->value();
    sendCommand(QString("TRAIN %1 ON %2").arg(id).arg(speed));
}

void ClientWindow::on_btnTrainOff_clicked()
{
    int id = ui->lineTrainId->text().toInt();
    sendCommand(QString("TRAIN %1 OFF").arg(id));
}

void ClientWindow::on_sliderSpeed_valueChanged(int value)
{
    ui->labelSpeedValue->setText(QString::number(value));
}


// ---------------------------
// Socket callbacks
// ---------------------------
void ClientWindow::onConnected()
{
    log("🟢 Conectado ao servidor!");
}

void ClientWindow::onDisconnected()
{
    log("🔴 Desconectado do servidor!");
}

void ClientWindow::onReadyRead()
{
    while (socket->bytesAvailable()) {
        QString line = socket->readLine().trimmed();
        log("[SERVER] " + line);
    }
}

void ClientWindow::onError(QAbstractSocket::SocketError)
{
    log("❌ Erro de socket: " + socket->errorString());
}
