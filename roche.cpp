#include "roche.h"

roche::roche() : obstacle()
{

    setResistance(7);
    setType(2);

ajouterdessin(new QPixmap(":/sprites/ressources/rock.png"));
}
