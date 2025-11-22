#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) : QMainWindow(parent),
                                              ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    tcpServer = new ControllerTcpServer(this);
    tcpServer->startServer(1234);

    connect(tcpServer, &ControllerTcpServer::commandReceived, this, [this](TrainCommand cmd)
            {

        int delayCalculado = (100 - cmd.velocidade + 1) * 3;

        if (cmd.id == 0) {
            for(int i = 1; i <= 7; i++){
                Trem* t = getTrem(i);
                if(t) {
                    t->setVelocidade(delayCalculado);
                    t->setEnable(cmd.enable);
                }
            }
        } else {
            Trem* t = getTrem(cmd.id);
            if(t) {
                t->setVelocidade(delayCalculado);
                t->setEnable(cmd.enable);
            } else {
                qDebug() << "ID invalido:" << cmd.id;
            }
        } });

    trem1 = new Trem(1, 200, 50, &semaphoreVector);
    trem2 = new Trem(2, 340, 50, &semaphoreVector);
    trem3 = new Trem(3, 480, 50, &semaphoreVector);
    trem4 = new Trem(4, 200, 200, &semaphoreVector);
    trem5 = new Trem(5, 480, 200, &semaphoreVector);
    trem6 = new Trem(6, 130, 300, &semaphoreVector);
    trem7 = new Trem(7, 550, 300, &semaphoreVector);

    semaphoreVector.at(9).semaphore.acquire(1);
    semaphoreVector.at(8).semaphore.acquire(1);

    for (int i = 1; i <= 7; i++)
    {
        Trem *t = getTrem(i);
        connect(t, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
        t->start();
    }
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

Trem *ServerWindow::getTrem(int id)
{
    switch (id)
    {
    case 1:
        return trem1;
    case 2:
        return trem2;
    case 3:
        return trem3;
    case 4:
        return trem4;
    case 5:
        return trem5;
    case 6:
        return trem6;
    case 7:
        return trem7;
    default:
        return nullptr;
    }
}

QLabel *ServerWindow::getLabelTrem(int id)
{
    switch (id)
    {
    case 1:
        return ui->labelTrem01;
    case 2:
        return ui->labelTrem02;
    case 3:
        return ui->labelTrem03;
    case 4:
        return ui->labelTrem04;
    case 5:
        return ui->labelTrem05;
    case 6:
        return ui->labelTrem06;
    case 7:
        return ui->labelTrem07;
    default:
        return nullptr;
    }
}

void ServerWindow::updateInterface(int id, int x, int y)
{
    QLabel *label = getLabelTrem(id);
    if (label)
    {
        label->setGeometry(x, y, 20, 20);
    }
}
