#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <omp.h>

#include "donnees_partie.h"

typedef struct
{
	int x_debut;	// Abscisse de départ
	int x_fin;	// Abscisse de fin
	int y_debut;	// Ordonnée de départ
	int y_fin;	// Ordonnée de fin
	int modification;	// Sert à savoir si l'on doit modifier l'abscisse de début ou de fin
	int incrementation_x;	// Sert à savoir si l'on incrémente ou décrémente la variable choisie

} Pions_joueur;	// Contient les variables nécessaire pour la fonction generation_pion

void clear_console(); // Vide la console
int choix_nombre_joueur();  // Demande le nombre de joueur
void vider_buffer();  // Vide le buffer pour le scanf

void afficher_plateau(int plateau[][TAILLE_PLATEAU]);	// Affiche tout le plateau de jeu
void afficher_classement(int classement[4], int nombre_joueur);	// Affiche le classement

void generation_terrain(DonneesPartie *variable_partie);	// Place les pions sur leurs emplacements de départ
void generation_pions(Pions_joueur *pions, DonneesPartie *variable_partie, int numero_joueur);	// Place les pions du joueur dont on donne le numéro et les coordonnées de ses pions


#endif
