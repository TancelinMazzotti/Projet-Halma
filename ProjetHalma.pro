TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
QMAKE_CFLAGS_DEBUG += -fopenmp
QMAKE_CFLAGS_RELEASE += -fopenmp
LIBS += -fopenmp

SOURCES += main.c \
    utilitaire.c \
    jeu.c \
    partie.c \
    donnees_partie.c \
    menu.c

HEADERS += \
    utilitaire.h \
    jeu.h \
    partie.h \
    donnees_partie.h \
    menu.h


