#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MaFenetre: public QWidget
{
    Q_OBJECT

    public:
        MaFenetre();

    public slots:
        void createGame1joueur();
        void createGame2joueur();
    private:
        QVBoxLayout *layout ;
        QPushButton *bouton1;
        QPushButton *bouton2;
        QPushButton *bouton3;
};

#endif // MAFENETRE_H
