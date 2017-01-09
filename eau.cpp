#include "eau.h"

eau::eau() : obstacle()
{
    setResistance(NMAX);
    setType(4);

ajouterdessin(new QPixmap(":/sprites/ressources/water.png"));
}
