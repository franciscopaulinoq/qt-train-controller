#ifndef CONTROLLERTCPSERVER_H
#define CONTROLLERTCPSERVER_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

struct TrainCommand
{
    int id;
    int velocidade;
    bool enable;
    TrainCommand() : id(0), velocidade(0), enable(true) {}
};

class ControllerTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ControllerTcpServer(QObject *parent = nullptr);
    void startServer(int port);

signals:
    void commandReceived(TrainCommand cmd);

public slots:
    void onNewConnection();
};

#endif // CONTROLLERTCPSERVER_H
