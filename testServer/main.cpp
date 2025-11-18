#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TestServer : public QTcpServer {
    Q_OBJECT
public:
    TestServer(QObject *parent = nullptr) : QTcpServer(parent) {
        connect(this, &QTcpServer::newConnection, this, &TestServer::onNewConnection);
    }

public slots:
    void onNewConnection() {
        QTcpSocket *client = nextPendingConnection();
        qDebug() << "Cliente conectado:" << client->peerAddress().toString();

        connect(client, &QTcpSocket::readyRead, this, [client]() {
            while (client->bytesAvailable()) {
                QString msg = client->readLine().trimmed();
                qDebug() << "[RECEBIDO]" << msg;

                // servidor de teste pode responder tbm:
                client->write(("OK: " + msg + "\n").toUtf8());
            }
        });

        connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestServer server;
    if (!server.listen(QHostAddress::Any, 1234)) {
        qDebug() << "Erro ao iniciar servidor!";
        return 1;
    }

    qDebug() << "Servidor de testes rodando na porta 1234...";

    return a.exec();
}

#include "main.moc"
