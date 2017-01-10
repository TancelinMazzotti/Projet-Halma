#ifndef PARTIE_H
#define PARTIE_H

#include "jeu.h"

int lancement_partie(DonneesPartie *variable_partie); // Lance la partie
int deroulement_tour(DonneesPartie *variable_partie);  // Permet de faire un tour de jeu complet
int fin_partie(DonneesPartie *variable_partie); // Détermine le moment où la pratie s'arrête

#endif
