#include "terrain.h"
#include <QDebug>



terrain::terrain()
{
        int taille_terrain_L = (L-(L/10*2)-25);
        int taille_terrain_C = C-25;
        srand(time(NULL));
        int nbarbre=rand() % 50;
        int i;


        for (i=0;i<nbarbre;i++) {
            ob.append(new arbre());
            ob[i]->setX(rand() %taille_terrain_L );
            ob[i]->setY(rand() %taille_terrain_C);

         for (int j=0; j<ob.length()-1; j++) {

                while ( (ob[j]->get_pos_x()==ob[i]->get_pos_x() ) && (ob[j]->get_pos_y()==ob[i]->get_pos_y() )){
                    srand(time(NULL));
                  ob[i]->setX(rand() %taille_terrain_L );
                  ob[i]->setY(rand() %taille_terrain_C);
                }

          }
      }

int nbroche=rand() % 15;
int n= i+nbroche;
        for (i=i;i<n;i++) {

            ob.append(new roche());
            ob[i]->setX(rand() %taille_terrain_L);
            ob[i]->setY(rand() %taille_terrain_C);

         for (int j=0; j<ob.length()-1; j++) {


                while ( (ob[j]->get_pos_x()==ob[i]->get_pos_x() ) && (ob[j]->get_pos_y()==ob[i]->get_pos_y() )){
                    srand(time(NULL));
                  ob[i]->setX(rand() %taille_terrain_L);
                  ob[i]->setY(rand() %taille_terrain_C);

                }


          }
        }


int nbfissure=rand() % 15;
n= i+nbfissure;
for (i=i;i<n;i++) {

    ob.append(new crevasse());
    ob[i]->setX(rand() %taille_terrain_L);
    ob[i]->setY(rand() %taille_terrain_C);

 for (int j=0; j<ob.length()-1; j++) {


        while ( (ob[j]->get_pos_x()==ob[i]->get_pos_x() ) && (ob[j]->get_pos_y()==ob[i]->get_pos_y() )){
            srand(time(NULL));
          ob[i]->setX(rand() %taille_terrain_L);
          ob[i]->setY(rand() %taille_terrain_C);

        }


  }
}

int nbeau=rand() % 15;
n= i+nbeau;

for (i=i;i<n;i++) {

    ob.append(new eau());
    ob[i]->setX(rand() %taille_terrain_L);
    ob[i]->setY(rand() %taille_terrain_C);

 for (int j=0; j<ob.length()-1; j++) {


        while ( (ob[j]->get_pos_x()==ob[i]->get_pos_x() ) && (ob[j]->get_pos_y()==ob[i]->get_pos_y() )){
            srand(time(NULL));
          ob[i]->setX(rand() %taille_terrain_L);
          ob[i]->setY(rand() %taille_terrain_C);

        }


  }
}

}
