#-------------------------------------------------
#
# Project created by QtCreator 2016-12-30T16:50:40
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Char
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    mafenetre.cpp \
    char.cpp \
    terrain.cpp \
    obstacle.cpp \
    roche.cpp \
    eau.cpp \
    crevasse.cpp \
    arbre.cpp

HEADERS  += \
    game.h \
    mafenetre.h \
    char.h \
    terrain.h \
    obstacle.h \
    roche.h \
    eau.h \
    crevasse.h \
    arbre.h

FORMS    +=

RESOURCES += \
    ressources.qrc
