#ifndef JEU_H
#define JEU_H

#include "utilitaire.h"
#include "partie.h"

int test_emplacement(int valeur_emplacement, int x, int y, const int plateau[][TAILLE_PLATEAU]);   // Test la valeur de l'emplacement du plateau
void selection_coordonne(int tableau_coord[]);                                                      // Demande les valeurs et remplis le tableau [X;Y] recuperer
int deplacer_pion(struct Partie *variable_partie);
int joueur_suivant(const int nombre_joueur, int numero_joueur, const int classement[]);                 // Retourne le numero du joueur suivant (MIN = 1 & MAX = 4)
int demande_fin_tour();

#endif
