#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include "MaFenetre.h"





int main(int argc, char *argv[]){
    QApplication a(argc, argv);




    MaFenetre myfenetre;
    myfenetre.show();



    return a.exec();
}
