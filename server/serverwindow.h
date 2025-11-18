#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include "trem.h"
#include <QMainWindow>

using namespace std;

namespace Ui
{
    class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

public slots:
    void updateInterface(int, int, int);

private:
    Ui::ServerWindow *ui;
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
};

#endif // SERVERWINDOW_H
