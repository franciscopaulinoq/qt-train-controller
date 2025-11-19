#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) : QMainWindow(parent),
                                              ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    trem1 = new Trem(1, 200, 50);
    connect(trem1, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem1->start();

    trem2 = new Trem(2, 340, 50);
    connect(trem2, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem2->start();

    trem3 = new Trem(3, 480, 50);
    connect(trem3, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem3->start();

    trem4 = new Trem(4, 200, 200);
    connect(trem4, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem4->start();

    trem5 = new Trem(5, 480, 200);
    connect(trem5, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem5->start();
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
    default:
        break;
    }
}
