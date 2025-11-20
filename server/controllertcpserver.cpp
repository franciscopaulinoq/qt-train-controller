#include "controllertcpserver.h"

ControllerTcpServer::ControllerTcpServer(QObject *parent) : QTcpServer(parent)
{
    connect(this, &QTcpServer::newConnection, this, &ControllerTcpServer::onNewConnection);
}

void ControllerTcpServer::startServer(int port)
{
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Erro: Não foi possível iniciar o servidor na porta" << port;
    }
    else
    {
        qDebug() << "Servidor TCP rodando na porta" << port << "...";
    }
}

void ControllerTcpServer::onNewConnection()
{
    QTcpSocket *client = nextPendingConnection();
    qDebug() << "Cliente conectado:" << client->peerAddress().toString();

    connect(client, &QTcpSocket::readyRead, this, [client]() {
        while (client->bytesAvailable()) {
            QString msg = client->readLine().trimmed();
            qDebug() << "[RECEBIDO]" << msg;

            // Responde ao cliente (Echo)
            client->write(("OK: " + msg + "\n").toUtf8());
        }
    });

    connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
}
