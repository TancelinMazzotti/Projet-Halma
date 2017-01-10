#ifndef MENU_H
#define MENU_H

#include "partie.h"

void afficher_menu();  // Affiche le menu
void menu();  // Menu d'acceuil
void regles();  // Affiche les règles du jeu
void recommencer(DonneesPartie *variable_partie); // Demande si l'utilisateur veux recommencer le jeu

#endif
