#ifndef CHAR_H
#define CHAR_H

#include <QPixmap>
#include <QPoint>

#define L 800

class Char
{
private:
    int angleHorizontal; //Angle du canon horizontalement de 0 à 360°
    int angleVertical; //0 à 90°
    int deplacement; //capacité de déplacement restant au tank initialisé à L/10
    int nbObus2;
    int nbObus3;
    bool alive;
    QPoint pos;
    int orientation; // orientation, 0 haut, 1 gauche, 2 bas, 3 droite
    QPixmap * texture_Corps;
    QPixmap * texture_Cannon;
    int vie;

public:
    Char(int numero_joueur);
    int getNbObus2() const;
    int getNbObus3() const;

    void enlever_pv(int degats);
    int get_pv();

    void tir_Obus(int type_obus);

    int getOrientation() const;
    void setOrientation(int value);

    void enlever_Deplacement(int value);
    bool deplacement_Possible(int penalite_deplacement);
    void reset_Deplacement();

    int get_nb_Deplacement_Possible();

    void setPosition(int x, int y);
    void changer_Position(int x, int y, int penalite_deplacement);
    int getX() const;
    int getY() const;

    QPixmap get_Texture_Corps();
    QPixmap get_Texture_Cannon();
    void setTextureCorps(QPixmap* newTexture);
    void setTextureCannon(QPixmap* newTexture);

    int getAngle_horizontal() const;
    int getAngle_vertical() const;

    void changer_angle_horizontal(int angle);
    void changer_angle_vertical(int angle);
};
#endif // CHAR_H
