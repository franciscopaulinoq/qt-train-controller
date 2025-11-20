#ifndef CONTROLLERTCPSERVER_H
#define CONTROLLERTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class ControllerTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ControllerTcpServer(QObject *parent = nullptr);
    void startServer(int port);

public slots:
    void onNewConnection();
};

#endif // CONTROLLERTCPSERVER_H
