#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "game.h"
#include "terrain.h"

#include <QGraphicsProxyWidget>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QDebug>

Game:: Game(int nbjoueur){

    scene = new QGraphicsScene();
    set_nbjoueur(nbjoueur);
    tour_de_jeu = 1;


    //Affichage du terrain


    ter = new terrain();
    int i;
    for (i=0;i<ter->ob.length();i++) {

        liste_texture_terrain.append(scene->addPixmap(ter->ob[i]->getDessin()));
        liste_texture_terrain[i]->setPos(ter->ob[i]->get_pos_x(),ter->ob[i]->get_pos_y());
    }

    // Creation des tanks
    char1 = new Char(1);
    int position_x=rand() % L -(L/5)-25;
    int position_y=rand()% C-25;
    char1->setPosition(position_x,position_y);
    while (collidingObstacle(*char1, ter->ob) || (position_x<0 || position_y<0) ) {
        position_x=rand() % L -(L/5)-25;
        position_y=rand()% C-25;
        char1->setPosition(position_x,position_y);
    }
    char1_texture = scene->addPixmap(char1->get_Texture_Corps());
    char1_texture_cannon = scene->addPixmap(char1->get_Texture_Cannon());
    char1_texture->setPos( position_x,position_y);
    char1_texture_cannon->setPos( position_x,position_y);

    char2 = new Char(2);
    position_x=rand() % L -(L/5)-25;
    position_y=rand()% C-25;
    char2->setPosition(position_x,position_y);
    while (collidingObstacle(*char2, ter->ob) || (position_x<0 || position_y<0) ) {
        position_x=rand() % L -(L/5)-25;
        position_y=rand()% C-25;
        char2->setPosition(position_x,position_y);
    }
    char2_texture = scene->addPixmap(char2->get_Texture_Corps());
    char2_texture_cannon = scene->addPixmap(char2->get_Texture_Cannon());
    char2_texture->setPos(position_x,position_y);
    char2_texture_cannon->setPos(position_x,position_y);



    //Tank Actif
    //Choisis Aleatoirement

    srand(time(NULL));
    premier_joueur = rand()%2; // 1 = Joueur rouge qui commence / 2 =Joueur bleu qui commence
    // CurrentChar == le char à qui c'est le tour de jouer
        if(premier_joueur==1){
            currentChar = char1;
            currentChar_texture = char1_texture;
            currentChar_texture_cannon = char1_texture_cannon;
        }else{
            currentChar = char2;
            currentChar_texture = char2_texture;
            currentChar_texture_cannon = char2_texture_cannon;
        }

    current_obus = 1;
    scene->setFocus();



    // create a view to visualize the scene
     this->setScene(scene);
     this->setFixedSize(L, C);

    this->setBackgroundBrush(QBrush(QColor(80, 148, 80), Qt::SolidPattern));

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

// Taille de zone de dessin
    scene->setSceneRect(0,0,L,C);

    //Taille du menu
        QGraphicsRectItem* menu = scene->addRect(L-L/10*2, 0, L/10*2, C);
        QBrush backgroundMenu(Qt::white);
         menu->setBrush(backgroundMenu);

         //Bouton Quitter
        QPushButton * quitter = new QPushButton;
        quitter->setText("Quitter");
        QObject::connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
        QGraphicsProxyWidget *proxy = scene->addWidget(quitter);
        proxy->setPos(L-L/10*2+30, C-quitter->height()-10);

         //Bouton selection obus type 1
        QPushButton *obus1=new QPushButton;
        obus1->setText("Obus 1");
        proxy=scene->addWidget(obus1);
        proxy->setPos(L-L/10*2 +30, 190);
        QObject::connect(obus1, SIGNAL(clicked()), this, SLOT(changer_obus1()));

        //Bouton selection obus type 2
        QPushButton *obus2=new QPushButton;
        obus2->setText("Obus 2 ");
        proxy=scene->addWidget(obus2);
        proxy->setPos(L-L/10*2 +30, 220);
         QObject::connect(obus2, SIGNAL(clicked()), this, SLOT(changer_obus2()));

         //Bouton selection obus type 3
        QPushButton *obus3=new QPushButton;
        obus3->setText("Obus 3 ");
        //manque le qObject
        proxy=scene->addWidget(obus3);
        proxy->setPos(L-L/10*2 +30, 250);
        QObject::connect(obus3, SIGNAL(clicked()), this, SLOT(changer_obus3()));

        QPalette fondblanc(Qt::black, Qt::white);

        //Texte Angle de Tir
        QLabel * angle = new QLabel;
        angle->setText("Angle de tir  :");
        angle->setPalette(fondblanc);
        proxy = scene->addWidget(angle);
        proxy->setPos(L-L/10*2+40, 290);


        //Bouton Tirer
        QPushButton *tirer=new QPushButton;
        tirer->setText("Tir");
        proxy=scene->addWidget(tirer);
        proxy->setPos(L-L/10*2 +30, 400);
        QObject::connect(tirer, SIGNAL(clicked()), this, SLOT(tir()));
        QObject::connect(tirer, SIGNAL(clicked()), this, SLOT(changerTour()));

    //Bouton changer de Tour
        QPushButton * changerTour = new QPushButton;
        changerTour->setText("Changer de tour");
        QObject::connect(changerTour, SIGNAL(clicked()), this, SLOT(changerTour()));
        proxy = scene->addWidget(changerTour);
        proxy->setPos(L-L/10*2+30, 450);


        QLabel * tour = new QLabel;
        tour->setText("Tour :");
        tour->setPalette(fondblanc);
        proxy = scene->addWidget(tour);
        proxy->setPos(L-L/10*2+30, 100);

        QLCDNumber * nbTour = new QLCDNumber;
        nbTour->setSegmentStyle(QLCDNumber::Flat);
        nbTour->setPalette(fondblanc);
        nbTour->display(tour_de_jeu);
        QObject::connect(this, SIGNAL(changementTour(int)), nbTour, SLOT(display(int)));
        proxy = scene->addWidget(nbTour);
        proxy->setPos(L-L/10*2+30+tour->width()+5, 100);


        QLabel *joueurnumero=new QLabel;
        joueurnumero->setText("Tour du joueur :");
        joueurnumero->setPalette(fondblanc);
        proxy= scene->addWidget(joueurnumero);
        proxy->setPos(L-L/10*2+20, 50);

        noir_bleu = QPalette(Qt::black, Qt::blue);
        noir_rouge = QPalette(Qt::black, Qt::red);

        joueur=new QLabel;

        //Couleur du premier joueur à jouer
               if(premier_joueur==1){

                   joueur->setText("Rouge");
                   joueur->setPalette(noir_rouge);
               }
               else{
                   joueur->setText("Bleu");
                   joueur->setPalette(noir_bleu);
       }

        proxy= scene->addWidget(joueur);
        proxy->setPos(L-L/10*2+20+joueurnumero->width()+5, 50);



        //Deplacements restants
        QLabel * text_deplacement = new QLabel;
        text_deplacement->setText("Point de Mouvement :");
        text_deplacement->setPalette(fondblanc);
        proxy = scene->addWidget(text_deplacement);
        proxy->setPos(L-L/10*2+30,130);

        QLCDNumber * nb_deplacement_restant = new QLCDNumber;
        nb_deplacement_restant->setSegmentStyle(QLCDNumber::Flat);
        nb_deplacement_restant->setPalette(fondblanc);
        nb_deplacement_restant->display(currentChar->get_nb_Deplacement_Possible());
        QObject::connect(this, SIGNAL(changement_deplacement(int)), nb_deplacement_restant, SLOT(display(int)));
        proxy = scene->addWidget(nb_deplacement_restant);
        proxy->setPos(L-L/10*2+30+tour->width()+5, 150);



        //Slider Cannon orientation Horizontale

        QSlider *slider_cannon_horizontal = new QSlider(Qt::Horizontal);
        slider_cannon_horizontal->setRange(0, 360);
        slider_cannon_horizontal->setGeometry(L-L/10*2+5, 20, L/10*2-10, 20);
        proxy = scene->addWidget(slider_cannon_horizontal);
        proxy->setPos(L-L/10*2+5, 310);

        QLCDNumber * orientation_cannon_display = new QLCDNumber;
        orientation_cannon_display->setSegmentStyle(QLCDNumber::Flat);
        orientation_cannon_display->setPalette(fondblanc);
        orientation_cannon_display->display(currentChar->getAngle_horizontal());
        QObject::connect(slider_cannon_horizontal, SIGNAL(valueChanged(int)), orientation_cannon_display, SLOT(display(int)));
        QObject::connect(slider_cannon_horizontal, SIGNAL(valueChanged(int)), this, SLOT(changer_angle_horizontal(int)));
        proxy = scene->addWidget(orientation_cannon_display);
        proxy->setPos(L-L/10*2+5, 330);


         //Slider Cannon orientation Vetical

        QSlider *slider_cannon_vertical = new QSlider(Qt::Horizontal);
        slider_cannon_vertical->setRange(0, 90);
        slider_cannon_vertical->setGeometry(L-L/10*2+5, 80, L/10*2-10, 20);
        proxy = scene->addWidget(slider_cannon_vertical);
        proxy->setPos(L-L/10*2+5, 350);

        QLCDNumber * orientation_vertical_cannon_display = new QLCDNumber;
        orientation_vertical_cannon_display->setSegmentStyle(QLCDNumber::Flat);
        orientation_vertical_cannon_display->setPalette(fondblanc);
        orientation_vertical_cannon_display->display(currentChar->getAngle_vertical());
        QObject::connect(slider_cannon_vertical, SIGNAL(valueChanged(int)), orientation_vertical_cannon_display, SLOT(display(int)));
        QObject::connect(slider_cannon_vertical, SIGNAL(valueChanged(int)), this, SLOT(changer_angle_vertical(int)));
        proxy = scene->addWidget(orientation_vertical_cannon_display);
        proxy->setPos(L-L/10*2+5, 370);

        //SI le signal fin du jeu est declenché, la fonction slot_findujeu se lance
        QObject::connect(this, SIGNAL(signal_findujeu(int)), this, SLOT(slot_findujeu(int)));

        if (premier_joueur==2) {
            controler_ia(ter->ob);
        }

}

int Game::get_nbjoueur()
{
    return nbjoueur;
}

void Game::set_nbjoueur(int entier)
{
    nbjoueur=entier;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    int origin_x = currentChar->getX();
    int origin_y = currentChar->getY();


    //
    if (get_nbjoueur()==1 && currentChar==char2) {
        event->ignore();
    }




    if(event->key() == Qt::Key_Left && origin_x >0){
            currentChar->changer_Position(-5, 0, 5);
            if(premier_joueur==1){
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_left.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_left.png"));
                }
            }
            else{
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_left.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_left.png"));
                }
            }


        }
        else if(event->key() == Qt::Key_Right && origin_x < L -(L/5)-25
                ){
            currentChar->changer_Position(5, 0, 5);
            if(premier_joueur==1){
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_right.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_rigth.png"));
                }
            }
            else{
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_rigth.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_right.png"));
                }
            }
        }
        else if(event->key() == Qt::Key_Up && origin_y>0){
            currentChar->changer_Position(0, -5, 5);
            if(premier_joueur==1){
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps.png"));
                }
            }
            else{
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2.png"));
                }
            }

        }
        else if(event->key() == Qt::Key_Down && origin_y <C -25){
            currentChar->changer_Position(0,5,5);
            if(premier_joueur==1){
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_down.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_down.png"));
                }
            }
            else{
                if(tour_de_jeu%2==0){
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_down.png"));
                }
                else{
                    currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_down.png"));
                }
            }
    }


    if(this->collidingObstacle(*currentChar, ter->ob)){

        for (int i=0;i<ter->ob.length();i++) {
            if(currentChar->getX() <ter->ob[i]->get_pos_x()+25 && currentChar->getX()+25 >ter->ob[i]->get_pos_x()
                    && currentChar->getY() < ter->ob[i]->get_pos_y()+25 && currentChar->getY()+25 >ter->ob[i]->get_pos_y()){
                switch(ter->ob[i]->getType()){
                    case 1: // arbre
                        currentChar->setPosition(origin_x, origin_y);
                        break;
                    case 2: // roche
                        currentChar->setPosition(origin_x, origin_y);
                        break;
                    case 3: //crevasse
                        currentChar->enlever_Deplacement(1);
                        break;
                     case 4: //eau
                        currentChar->setPosition(origin_x, origin_y);
                        break;
                default:
                        break;
                }
            }
        }

    }

    if(this->collidingChar()){
         currentChar->setPosition(origin_x, origin_y);
    }


    currentChar_texture->setPos(currentChar->getX(), currentChar->getY());
    currentChar_texture_cannon->setPos(currentChar->getX(), currentChar->getY());



    emit changement_deplacement(currentChar->get_nb_Deplacement_Possible());
}

void Game::changerTour() //Fonction declenchée par des actions, remplace tout les elements du CurrentChar par le char du tour suivant
{
    tour_de_jeu += 1;
       if(premier_joueur==1){
           if(tour_de_jeu%2==1){
              char1->changer_angle_horizontal(currentChar->getAngle_horizontal());
               char1->changer_angle_vertical(currentChar->getAngle_vertical());
              currentChar = char1;
              currentChar_texture = char1_texture;
              currentChar_texture_cannon = char1_texture_cannon;
              joueur->setText("Rouge");
              joueur->setPalette(noir_rouge);
           }
           else{
              char2->changer_angle_horizontal(currentChar->getAngle_horizontal());
              char2->changer_angle_vertical(currentChar->getAngle_vertical());
              currentChar = char2;
              currentChar_texture = char2_texture;
              currentChar_texture_cannon = char2_texture_cannon;
              joueur->setText("Bleu");
              joueur->setPalette(noir_bleu);
           }
          }
          else{
           if(tour_de_jeu%2==0){
              char1->changer_angle_horizontal(currentChar->getAngle_horizontal());
               char1->changer_angle_vertical(currentChar->getAngle_vertical());
              currentChar = char1;
              currentChar_texture = char1_texture;
              currentChar_texture_cannon = char1_texture_cannon;
              joueur->setText("Rouge");
              joueur->setPalette(noir_rouge);
           }
           else{
              char2->changer_angle_horizontal(currentChar->getAngle_horizontal());
              char2->changer_angle_vertical(currentChar->getAngle_vertical());
              currentChar = char2;
              currentChar_texture = char2_texture;
              currentChar_texture_cannon = char2_texture_cannon;
              joueur->setText("Bleu");
              joueur->setPalette(noir_bleu);
           }
          }

    currentChar->reset_Deplacement(); //On redonne tout les points de deplacement au char à qui c'est le tour de jouer
    emit changement_deplacement(currentChar->get_nb_Deplacement_Possible()); //On update le compteur de deplacement
    emit changementTour(tour_de_jeu);
    if(char1->get_pv()<1){
        emit signal_findujeu(2); // Si le joueur 1 est mort, fin du jeu, joueur 2 gagne
    }
    if(char2->get_pv()<1){
        emit signal_findujeu(1); // Si le joueur 2 est mort, fin du jeu, joueur 1 gagne
    }

    int joueur_ia=get_nbjoueur();
    if (joueur_ia==1 && currentChar==char2) {
        controler_ia(ter->ob);

    }
}

void Game::controler_ia(QList<obstacle *> list_ob)
{
    int depla=0;
    int char_ennemy_x=char1->getX();
    int char_ennemy_y=char1->getY();
    while (!(collidingObstacle(*currentChar,list_ob)) && currentChar->getX() >0 && currentChar->getY()>0 && depla<15) {


            QTime dieTime = QTime::currentTime().addMSecs( 50 );
            while( QTime::currentTime() < dieTime )
            {
                QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }
        //si le tank ennemy est à sa droite
            if (char_ennemy_x>currentChar->getX()) {
             currentChar->changer_Position(5,0,5);
             currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_right.png"));
            }
        //à sa gauche
            if (char_ennemy_x<currentChar->getX()) {
                currentChar->changer_Position(-5,0,5);

              currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_left.png"));

            }

          //en bas
            if (char_ennemy_y>currentChar->getY()) {
                currentChar->changer_Position(0,5,5);

              currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2_down.png"));

              }

            //en haut
             if (char_ennemy_y<currentChar->getY()) {
                 currentChar->changer_Position(0,-5,5);
                currentChar_texture->setPixmap(QPixmap(":/sprites/ressources/Char_corps_2.png"));

              }



        depla++;
    }

    //si il ne peut plus se déplacer à cause d'un obstacle :
    if (collidingObstacle(*currentChar,list_ob) && depla<10) {
        for (int i=0;i<list_ob.length();i++) {
            if(currentChar->getX() < list_ob[i]->get_pos_x()+25 && currentChar->getX()+25 >list_ob[i]->get_pos_x()
                    && currentChar->getY() < list_ob[i]->get_pos_y()+25 && currentChar->getY()+25 >list_ob[i]->get_pos_y()
                    && (list_ob[i]->getType()==1 || list_ob[i]->getType()==2)){
                tirer(list_ob[i]->get_pos_x(), list_ob[i]->get_pos_y(),1);
            }
            else if (currentChar->getX() < list_ob[i]->get_pos_x()+25 && currentChar->getX()+25 >list_ob[i]->get_pos_x()
                        && currentChar->getY() < list_ob[i]->get_pos_y()+25 && currentChar->getY()+25 >list_ob[i]->get_pos_y()
                        && (list_ob[i]->getType()==3)){
                     currentChar->changer_Position(list_ob[i]->get_pos_x(),list_ob[i]->get_pos_y(),0);
                     list_ob.removeAt(i);
                     //si le tank touche est coincé par une fissure, il va dessus et on l'enleve de la liste


            }
            else if (currentChar->getX() < list_ob[i]->get_pos_x()+25 && currentChar->getX()+25 >list_ob[i]->get_pos_x()
                        && currentChar->getY() < list_ob[i]->get_pos_y()+25 && currentChar->getY()+25 >list_ob[i]->get_pos_y()
                        && (list_ob[i]->getType()==4)){
                     currentChar->changer_Position(list_ob[i]->get_pos_x(),list_ob[i]->get_pos_y(),0);
                     //le char se noie ici
                     qDebug() << "noyé";

            }
        }
    }
    else if (char_ennemy_x-currentChar->getX()<100 && char_ennemy_y-currentChar->getY()<100){
        tirer(char1->getX(), char1->getY(),2);
        qDebug() << "kaboum";
    }


    currentChar_texture->setPos(currentChar->getX(), currentChar->getY());
    currentChar_texture_cannon->setPos(currentChar->getX(), currentChar->getY());



    emit changement_deplacement(currentChar->get_nb_Deplacement_Possible());


    changerTour();
}

void Game::changer_angle_horizontal(int angle) //Fonction appelée par le slider horizontal pour changer l'angle du CurrentChar
{
    currentChar->changer_angle_horizontal(angle);
}

void Game::changer_angle_vertical(int angle)  //Fonction appelée par le slider vertical pour changer l'angle du CurrentChar
{
    currentChar->changer_angle_vertical(angle);
}

void Game::tir() //Fonction de tir qui calcul l'endroit ou l'obus va tomber suivant les angles du CurrentChar
{
    int radian_measure = (2 * PI / 360 ) * (360 - currentChar->getAngle_horizontal());
    int distance = currentChar->getAngle_vertical()*2;
    int depart_x = currentChar->getX() + (25/2);
    int depart_y = currentChar->getY() +(25/2);
    int tir_x =  depart_x + distance *  cos(radian_measure);
    int tir_y =  depart_y + distance *  sin(radian_measure);
    this->tirer(tir_x, tir_y, current_obus);
}

// Les fonctions de changement de type d'obus
void Game::changer_obus1()
{
        current_obus = 1;
}

void Game::changer_obus2()
{
        current_obus = 2;
}

void Game::changer_obus3()
{
    current_obus = 3;
}

//Fonction de fin du jeu qui affiche le vainqueur
void Game::slot_findujeu(int joueur)
{
        QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,L,C);
        item1->setBrush(QBrush(Qt::white));
        this->scene->addItem(item1);

        noir_bleu = QPalette(Qt::black, Qt::blue);
        noir_rouge = QPalette(Qt::black, Qt::red);

        QLabel* gagnant = new QLabel;
        gagnant->setText("Le Joueur " +QString::number( joueur) + " a gagné !");
        QFont font;
         font.setPointSize(32);
         gagnant->setFont(font);

        if(joueur==1){
               gagnant->setPalette(noir_rouge);
        }
        else{
                gagnant->setPalette(noir_bleu);
        }
        QGraphicsProxyWidget *widget_proxy = scene->addWidget(gagnant);
        widget_proxy->setPos(L/2- gagnant->width()/2, C/2 - gagnant->height()/2);
}

// Fonction qui retourne vrai si le char est sur un obstacle, non sinon
bool Game::collidingObstacle(Char current_char, QList<obstacle *> list_ob){
    for (int i=0;i<list_ob.length();i++) {
        if(current_char.getX() < list_ob[i]->get_pos_x()+25 && current_char.getX()+25 >list_ob[i]->get_pos_x()
                && current_char.getY() < list_ob[i]->get_pos_y()+25 && current_char.getY()+25 >list_ob[i]->get_pos_y()){
            return true;
        }
    }
    return false;
}
//Fonction qui retourne vrai si les chars se rencontrent, faux sinon
bool Game::collidingChar(){
            if(char1->getX() < char2->getX()+25){
                if(char1->getX()+25 > char2->getX()){
                    if(char1->getY() < char2->getY()+25){
                        if(char1->getY()+25 > char2->getY()){
                            return true;
                        }
                    }
                }

            }
            return false;
}
//Fonction de tir à une position (x,y) selon le type d'obus et effectue les degats sur les elements

void Game::tirer(int x, int y, int typeobus)
{
    //son d'un tir
    QMediaPlayer *music= new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sprites/ressources/12780.wav"));
    music->play();

    QPen pen;
    pen.setColor(Qt::white);
    int w,z;
    if (typeobus==1) {
       w=10;
       z=10;
    }
    else if (typeobus==2) {
        w=20;
        z=20;

    }
    else {
        w=35;
        z=35;
    }
    QGraphicsEllipseItem *tir=new QGraphicsEllipseItem(x-w,y-z,w*2,z*2);
    tir->setBrush(QBrush(QColor(164, 100, 34)));
    tir->setZValue(-1);
    scene->addItem(tir);
//Regarde si l'obus touche le joueur 1
    if(secroise(x,y,char1->getX(),char1->getY(), z)){
        if (typeobus==1){
            char1->enlever_pv(2);
        }
        if (typeobus==2){
            char1->enlever_pv(5);
        }
        if (typeobus==3){
            char1->enlever_pv(10);
        }
    }
//Regarde si l'obus touche le joueur 2
    if(secroise(x,y,char2->getX(),char2->getY(), z)){
        if (typeobus==1){
            char2->enlever_pv(2);
        }
        if (typeobus==2){
            char2->enlever_pv(5);
        }
        if (typeobus==3){
            char2->enlever_pv(10);
        }
    }
//Regarde si l'obus touche des obstacles
    for (int i=0; i<ter->ob.length();i++) {
        if (secroise (x,y,ter->ob[i]->get_pos_x(), ter->ob[i]->get_pos_y(),z))
        {
            if (typeobus==1){
            ter->ob[i]->setResistance(ter->ob[i]->getResistance()-2);
            }
            else if (typeobus==2) {
                ter->ob[i]->setResistance(ter->ob[i]->getResistance()-5);
            }
            else
            {
                ter->ob[i]->setResistance(ter->ob[i]->getResistance()-10);

            }
            if(ter->ob[i]->getType()==1){
                if(ter->ob[i]->getResistance()<=0){
                    ter->ob.removeAt(i);
                    scene->removeItem(liste_texture_terrain[i]);
                    liste_texture_terrain.removeAt(i);
                }
                else{
                    liste_texture_terrain[i]->setPixmap(QPixmap(":/sprites/ressources/tree_dammaged.png"));
                }
            }
            if(ter->ob[i]->getType()==2){
                if(ter->ob[i]->getResistance()<=0){
                    ter->ob.removeAt(i);
                    scene->removeItem(liste_texture_terrain[i]);
                    liste_texture_terrain.removeAt(i);
                }
                else{
                    liste_texture_terrain[i]->setPixmap(QPixmap(":/sprites/ressources/rock_dammaged.png"));
                }
            }

        }
    }



}

bool Game::secroise(int cercle_x, int cercle_y, int obj_x, int obj_y, int cercle_r)
{
    int circleDistance_x = abs(cercle_x - (obj_x+(25/2)));
    int circleDistance_y = abs(cercle_y - (obj_y+(25/2)));

    if (circleDistance_x > (25/2 + cercle_r)) { return false; }
    else if (circleDistance_y > (25/2 + cercle_r)) { return false; }

    else if (circleDistance_x <= (25/2)) { return true; }
    else if (circleDistance_y <= (25/2)) { return true; }

    int cornerDistance = ((circleDistance_x - 25/2)^2) + ((circleDistance_y - 25/2)^2);

    return (cornerDistance <= (cercle_r^2));

}

