#include "trem.h"

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 300;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run, this);
}

void Trem::run()
{
    while (true)
    {
        switch (id)
        {
        case 1:
            if (enable)
            {
                emit updateGUI(id, x, y);
                if (y == 50 && x < 270)
                    x += 10;
                else if (x == 270 && y < 150)
                    y += 10;
                else if (x > 130 && y == 150)
                    x -= 10;
                else
                    y -= 10;
            }
            break;
        case 2:
            emit updateGUI(id, x, y);
            if (y == 50 && x > 270)
                x -= 10;
            else if (x == 270 && y < 150)
                y += 10;
            else if (x < 410 && y == 150)
                x += 10;
            else
                y -= 10;
            break;
        case 3:
            emit updateGUI(id, x, y);
            if (y == 50 && x < 550)
                x += 10;
            else if (x == 550 && y < 150)
                y += 10;
            else if (x > 410 && y == 150)
                x -= 10;
            else
                y -= 10;
            break;
        case 4:
            emit updateGUI(id, x, y);
            if (y == 150 && x > 200)
                x -= 10;
            else if (x == 200 && y < 250)
                y += 10;
            else if (x < 480 && y == 250)
                x += 10;
            else
                y -= 10;
            break;
        case 5:
            emit updateGUI(id, x, y);
            if (y == 150 && x > 200)
                x -= 10;
            else if (x == 200 && y < 250)
                y += 10;
            else if (x < 480 && y == 250)
                x += 10;
            else
                y -= 10;
            break;
        case 6:
            emit updateGUI(id, x, y);
            if (y == 250 && x < 340)
                x += 10;
            else if (x == 340 && y < 350)
                y += 10;
            else if (x > 130 && y == 350)
                x -= 10;
            else
                y -= 10;
            break;
        case 7:
            emit updateGUI(id, x, y);
            if (y == 250 && x < 550)
                x += 10;
            else if (x == 550 && y < 350)
                y += 10;
            else if (x > 340 && y == 350)
                x -= 10;
            else
                y -= 10;
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}
