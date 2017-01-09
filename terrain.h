#ifndef TERRAIN_H
#define TERRAIN_H
#include <random>
#include <time.h>
#include "obstacle.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QList>
#include <typeinfo>
#include <QGraphicsItem>
#include "arbre.h"
#include "eau.h"
#include "crevasse.h"
#include "roche.h"
#include <QDebug>



#define L 800
#define C 550


class terrain
{

public:
    QList<obstacle *> ob;
    terrain();
};

#endif // TERRAIN_H
