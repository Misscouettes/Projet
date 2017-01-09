#include "obstacle.h"



obstacle::obstacle()
{

}


int obstacle::getType(){
    return this->type;
}

void obstacle::setResistance(int res)
{
    this->resistance=res;
}

void obstacle::setType(int type)
{
    this->type=type;
}

void obstacle::setX(int x)
{
    this->position.setX(x);
}

void obstacle::setY(int y)
{
    this->position.setY(y);
}

int obstacle::getResistance()
{
    return this->resistance;
}


void obstacle::ajouterdessin(QPixmap *newdraw)
{
    dessin=newdraw;
}

QPixmap obstacle::getDessin()
{
    return *dessin;
}

int obstacle::get_pos_x()
{
    return this->position.x();

}
int obstacle::get_pos_y()
{
    return this->position.y();

}

