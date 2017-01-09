#include "mafenetre.h"
#include "Game.h"


void MaFenetre::createGame1joueur()
{
     Game* game = new Game(1);
     layout->addWidget(game);

     bouton1->hide();
     bouton2->hide();
     bouton3->hide();
     this->setFixedSize(layout->sizeHint());
}

void MaFenetre::createGame2joueur()
{
     Game* game = new Game(2);
     layout->addWidget(game);

     bouton1->hide();
     bouton2->hide();
     bouton3->hide();
     this->setFixedSize(layout->sizeHint());
}



MaFenetre::MaFenetre()
{
    setFixedSize(600, 350);


    bouton1 = new QPushButton("1 Joueur");
    bouton2 = new QPushButton("2 Joueurs");
    bouton3 = new QPushButton("Exit");


    bouton1->setFixedHeight(50);
    bouton2->setFixedHeight(50);
    bouton3->setFixedHeight(50);

   layout = new QVBoxLayout;
         layout->setContentsMargins(0,0,0,0);
        layout->addWidget(bouton1);
        layout->addWidget(bouton2);
        layout->addWidget(bouton3);
        this->setLayout(layout);

        QObject::connect(bouton1, SIGNAL(clicked()), this, SLOT(createGame1joueur()));
        QObject::connect(bouton2, SIGNAL(clicked()), this, SLOT(createGame2joueur()));

        this->show();




}
