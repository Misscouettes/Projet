#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QPixmap>
#include <QPoint>


class obstacle
{
private :
    int resistance;
    int type;
    QPixmap *dessin;
    QPoint position;


public:
    obstacle();
    obstacle(int res, int typ, int x, int y);
    int getResistance();
    int getType();
    void setResistance(int res);
    void setType(int type);
    void setX(int x);
    void setY(int y);
    void ajouterdessin(QPixmap *newdraw);
    QPixmap getDessin();
    int get_pos_x();
    int get_pos_y();
};

#endif // OBSTACLE_H
