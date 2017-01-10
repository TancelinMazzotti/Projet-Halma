#ifndef DONNNEES_PARTIE_H
#define DONNNEES_PARTIE_H

#define TAILLE_PLATEAU 10

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int num_joueur; // Numéro du joueur qui joue
    int nombre_joueur;  // Nombre de joueurs dans la partie
    int plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];  // Plateau du jeu
    int classement[4];  // Tableau de classement des joueurs ayant fini
    int coord_pion_selectionner[2]; //  Coordonnées du pion sélectionné par un joueur
    int coord_destination_pion[2];  //  Coordonnées de la destination du pion
    int resultat_deplacement; // Indique le type de déplacement effectué
    int **tableau_destination; // Tableau qui stock toute les destinations possible
    int taille_tableau_destination; // Taille du tableau des destinations
}DonneesPartie;

int char_to_int(char chiffre);  // Convertisseur char en int
char int_to_char(int chiffre);	// Convertisseur int en char

int sauvegarde(DonneesPartie * donnes_a_sauvegarder); // Sauvegarde la partie
int charger(DonneesPartie * donnees_a_charger); // Chargement de la derniere sauvegarde

#endif
