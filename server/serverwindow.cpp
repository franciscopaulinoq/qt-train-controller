#include "serverwindow.h"
#include "ui_serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) : QMainWindow(parent),
                                              ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    trem1 = new Trem(1, 180, 120);
    connect(trem1, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem1->start();

    trem2 = new Trem(2, 320, 120);
    connect(trem2, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem2->start();

    trem3 = new Trem(3, 460, 120);
    connect(trem3, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    trem3->start();
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
    default:
        break;
    }
}
