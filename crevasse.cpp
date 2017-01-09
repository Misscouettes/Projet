#include "crevasse.h"

crevasse::crevasse() : obstacle()
{
    setResistance(-2);
    setType(3);

ajouterdessin(new QPixmap(":/sprites/ressources/fissure.png"));
}
