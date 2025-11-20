#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QTcpSocket>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>

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

void ClientWindow::sendJson(const QJsonObject &jsonObj)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QJsonDocument doc(jsonObj);
        
        QByteArray data = doc.toJson(QJsonDocument::Compact);
        
        socket->write(data);
        socket->flush();
        
        log("[ENVIADO] " + QString::fromUtf8(data));
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

    QJsonObject json;
    json["id"] = id;
    json["velocidade"] = speed;
    json["enable"] = true;

    sendJson(json);
}

void ClientWindow::on_btnTrainOff_clicked()
{
    int id = ui->lineTrainId->text().toInt();

    QJsonObject json;
    json["id"] = id;
    json["velocidade"] = 0;
    json["enable"] = false;

    sendJson(json);
}

void ClientWindow::on_sliderSpeed_valueChanged(int value)
{
    ui->labelSpeedValue->setText(QString::number(value));
    
    // OPCIONAL: Se você quiser que o trem mude de velocidade 
    // EM TEMPO REAL enquanto arrasta o slider, descomente abaixo:
    
    /*
    int id = ui->lineTrainId->text().toInt();
    // Só envia se tiver um ID válido (>0) para não spamar erro
    if (id > 0 && socket->state() == QAbstractSocket::ConnectedState) {
        QJsonObject json;
        json["id"] = id;
        json["velocidade"] = value;
        json["enable"] = true; 
        sendJson(json);
    }
    */
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
        QByteArray data = socket->readAll();
        log("[SERVER] " + QString::fromUtf8(data));
    }
}

void ClientWindow::onError(QAbstractSocket::SocketError)
{
    log("❌ Erro de socket: " + socket->errorString());
}