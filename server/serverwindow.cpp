#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) : QMainWindow(parent),
                                              ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    tcpServer = new ControllerTcpServer(this);

    connect(tcpServer, &ControllerTcpServer::commandReceived, this, [this](TrainCommand cmd) {

        switch(cmd.id) {
        case 1:
            trem1->setVelocidade((100 - cmd.velocidade + 1) * 3);
            trem1->setEnable(cmd.enable);
            break;
        case 2:
            trem2->setVelocidade((100 - cmd.velocidade + 1)*3);
            trem2->setEnable(cmd.enable);
            break;
        case 3:
            trem3->setVelocidade((100 - cmd.velocidade + 1)*3);
            trem3->setEnable(cmd.enable);
            break;
        case 4:
            trem4->setVelocidade((100 - cmd.velocidade + 1)*3);
            trem4->setEnable(cmd.enable);
            break;
        case 5:
            trem5->setVelocidade((100 - cmd.velocidade + 1)*3);
            trem5->setEnable(cmd.enable);
            break;
        case 6:
            trem6->setVelocidade((100 - cmd.velocidade + 1)*3);
            trem6->setEnable(cmd.enable);
            break;
        case 7:
            trem7->setVelocidade((100 - cmd.velocidade + 1)*3);
            trem7->setEnable(cmd.enable);
            break;
        default:
            qDebug() << "ID de trem desconhecido:" << cmd.id;
            break;
        }
    });

    tcpServer->startServer(1234);

    trem1 = new Trem(1, 200, 50, &semaphoreVector);
    connect(trem1, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem1->start();

    trem2 = new Trem(2, 340, 50, &semaphoreVector);
    connect(trem2, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem2->start();

    trem3 = new Trem(3, 480, 50, &semaphoreVector);
    connect(trem3, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem3->start();

    trem4 = new Trem(4, 200, 200, &semaphoreVector);
    connect(trem4, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    semaphoreVector.at(9).semaphore.acquire(1);
    trem4->start();

    trem5 = new Trem(5, 480, 200, &semaphoreVector);
    connect(trem5, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    semaphoreVector.at(8).semaphore.acquire(1);
    trem5->start();

    trem6 = new Trem(6, 130, 300, &semaphoreVector);
    connect(trem6, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem6->start();

    trem7 = new Trem(7, 550, 300, &semaphoreVector);
    connect(trem7, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem7->start();
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::updateInterface(int id, int x, int y)
{
    switch (id)
    {
    case 1:
        ui->labelTrem01->setGeometry(x, y, 20, 20);
        break;
    case 2:
        ui->labelTrem02->setGeometry(x, y, 20, 20);
        break;
    case 3:
        ui->labelTrem03->setGeometry(x, y, 20, 20);
        break;
    case 4:
        ui->labelTrem04->setGeometry(x, y, 20, 20);
        break;
    case 5:
        ui->labelTrem05->setGeometry(x, y, 20, 20);
        break;
    case 6:
        ui->labelTrem06->setGeometry(x, y, 20, 20);
        break;
    case 7:
        ui->labelTrem07->setGeometry(x, y, 20, 20);
        break;
    default:
        break;
    }
}
