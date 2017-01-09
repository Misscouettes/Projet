#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QColor>
#include <QLabel>
#include "char.h"
#include "terrain.h"
#include <math.h>
#include <QTime>

#define PI 3.14159265


class Game :public QGraphicsView{

        Q_OBJECT
private :
    int nbjoueur;
public:


    Game(int nbjoueur);
    QGraphicsScene * scene;
    int premier_joueur;
    Char* char1;
    Char* char2;

    QGraphicsPixmapItem* char1_texture;
    QGraphicsPixmapItem* char1_texture_cannon;
    QGraphicsPixmapItem* char2_texture;
    QGraphicsPixmapItem* char2_texture_cannon;

    Char* currentChar;
    QGraphicsPixmapItem* currentChar_texture;
    QGraphicsPixmapItem* currentChar_texture_cannon;

    QLabel *joueur;
    QPalette noir_bleu;
    QPalette noir_rouge;

    terrain *ter;
    QList<QGraphicsPixmapItem *> liste_texture_terrain;

    int tour_de_jeu;

    int current_obus;
    int get_nbjoueur();
    void set_nbjoueur(int entier);

    void keyPressEvent(QKeyEvent *event);
    bool collidingObstacle(Char current_char, QList<obstacle *> list_ob);
    bool collidingChar();
    void tirer(int x, int y, int typeobus);
    bool secroise(int cercle_x, int cercle_y, int obj_x, int obj_y, int cercle_r);

    void controler_ia(QList<obstacle *> list_ob);
public slots:
    void changerTour();
    void changer_angle_horizontal(int angle);
    void changer_angle_vertical(int angle);
    void tir();
    void changer_obus1();
    void changer_obus2();
    void changer_obus3();
    void slot_findujeu(int joueur);

signals:
    void changementTour(int tour);
    void changement_deplacement(int nb_deplacement_restant);
    void signal_findujeu(int joueur);

};

#endif // GAME_H
