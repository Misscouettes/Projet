#include "char.h"
#include "QDebug"

Char::Char(int numero_joueur)
{
    this->angleHorizontal = 0;
    this->angleVertical = 0;
    this->deplacement = L/10;
    this->nbObus2 = 6;
    this->nbObus3 = 1;
    this->alive = true;
    this->vie = 10;
    this->orientation = 0; // orientation, 0 haut, 1 gauche, 2 bas, 3 droite
    if(numero_joueur == 1){
        this->texture_Corps = new QPixmap(":/sprites/ressources/Char_corps.png") ;
        this->texture_Cannon = new QPixmap(":/sprites/ressources/Char_cannon.png") ;
    }
    else{
        this->texture_Corps = new QPixmap(":/sprites/ressources/Char_corps_2.png") ;
        this->texture_Cannon = new QPixmap(":/sprites/ressources/Char_cannon.png") ;
    }

}

int Char::getNbObus2() const{
    return this->nbObus2;
}

int Char::getNbObus3() const{
    return this->nbObus2;
}

void Char::enlever_pv(int degats)
{
    this->vie = this->vie - degats;
}

int Char::get_pv()
{
    return this->vie;
}

void Char::tir_Obus(int type_obus){
    switch(type_obus){
        case 2:
            this->nbObus2 -= 1;
            break;
        case 3:
            this->nbObus3 -= 1;
            break;
    default:
            break;
    }
}

int Char::getOrientation() const{
    return this->orientation;
}

void Char::setOrientation(int value){
    this->orientation = value;
}

void Char::enlever_Deplacement(int value){
    this->deplacement = this->deplacement-value;
}

bool Char::deplacement_Possible(int penalite_deplacement){
    if(this->deplacement>= penalite_deplacement){

        return true;
    }
    return false;
}

void Char::reset_Deplacement(){
    this->deplacement = L/10;
}


QPixmap Char::get_Texture_Corps(){
    return *texture_Corps;
}

QPixmap Char::get_Texture_Cannon(){
    return *texture_Cannon;
}

void Char::setTextureCorps(QPixmap* newTexture){
    this->texture_Corps = newTexture;
}

void Char::setTextureCannon(QPixmap* newTexture){
    this->texture_Cannon= newTexture;
}


void Char::changer_Position(int x, int y, int penalite_deplacement){

    if(this->deplacement_Possible(penalite_deplacement)){
        this->pos.setX(this->pos.x()+x);
        this->pos.setY(this->pos.y()+y);
        this->enlever_Deplacement(penalite_deplacement);
    }
}

int Char::getX() const{
    return this->pos.x();
}
int Char::getY() const{
    return this->pos.y();
}


int Char::get_nb_Deplacement_Possible(){
    return this->deplacement/5;
}

void Char::setPosition(int x, int y){
    this->pos.setX(x);
    this->pos.setY(y);
}

int Char::getAngle_horizontal() const{
    return this->angleHorizontal;
}

int Char::getAngle_vertical() const{
    return this->angleVertical;
}

void Char::changer_angle_horizontal(int angle)
{
    this->angleHorizontal = angle;
}

void Char::changer_angle_vertical(int angle)
{
    this->angleVertical = angle;
}

