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

    connect(client, &QTcpSocket::readyRead, this, [this, client]() {
        while (client->bytesAvailable()) {
            QByteArray data = client->readAll();

            QJsonDocument doc = QJsonDocument::fromJson(data);

            if (doc.isNull() || !doc.isObject()) {
                qDebug() << "Recebido dado inválido (não é JSON):" << data;
                client->write("Erro: Formato JSON invalido\n");
                continue;
            }

            QJsonObject json = doc.object();

            TrainCommand cmd;

            cmd.id = json["id"].toInt(0);
            cmd.velocidade = json["velocidade"].toInt(1);
            cmd.enable = json["enable"].toBool(true);

            qDebug() << "Comando Processado -> ID:" << cmd.id
                     << " Vel:" << cmd.velocidade
                     << " Enable:" << cmd.enable;

            emit commandReceived(cmd);

            client->write("Comando recebido com sucesso\n");
        }
    });

    connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
}
