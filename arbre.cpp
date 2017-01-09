#include "arbre.h"
#include "obstacle.h"

arbre::arbre(): obstacle()
{

    setResistance(1);
    setType(1);

ajouterdessin(new QPixmap(":/sprites/ressources/tree.png"));
}
