#include "partie.h"

int deroulement_tour(DonneesPartie *variable_partie)  // Permet de faire un tour de jeu complet
{
    do
    {
        clear_console();
        afficher_plateau(variable_partie->plateau); // On affiche le plateau
        printf("JOUEUR %d a vous de jouer ! \n\n",variable_partie->num_joueur); // On indique quel joueur doit jouer

        do
        {
          printf("Selectionner un pion\n");
          selection_coordonne(variable_partie->coord_pion_selectionner);  // Selection du pion
        } while(test_emplacement(variable_partie->num_joueur,variable_partie->coord_pion_selectionner[0], variable_partie->coord_pion_selectionner[1], variable_partie->plateau) == 0);

        prevision(variable_partie); // On va regarder les déplacements que l'on peut faire à partir du pion sélectionné

        afficher_plateau(variable_partie->plateau);
        printf("Selectionner destination\n");
        selection_coordonne(variable_partie->coord_destination_pion); // Selection de la destinantion du pion

        // deplacer_pion sera un peu modifiée par la suite
        variable_partie->resultat_deplacement = deplacer_pion(variable_partie);

        clear_console();
        afficher_plateau(variable_partie->plateau);

        // Affichage les informations sur le deplacemnt effectué
        if(variable_partie->resultat_deplacement == 0)
            printf("\nERREUR: Deplacemnt impossible\n\n");
        else if(variable_partie->resultat_deplacement == 1)
            printf("\nDeplacemnt standard reussie\n\n");

        // Demande fin du tour en focntion du resultat du deplacemnt
        if(variable_partie->resultat_deplacement != 1)
        {
          printf("Appuyez sur la touche 'ENTRER': ");
          vider_buffer();
          while(getchar() != '\n');
        }

    }while (variable_partie->resultat_deplacement != 1); // Tant que le deplacement n'est pas valide
    variable_partie->resultat_deplacement = 0;

    // Test si le joueur a fini et initialisation des différentes structures en fonction numéro du joueur

    // Initialisation d'une variable taille pour savoir la taille de nos pyramides à tester
    int taille;

    if (variable_partie->nombre_joueur == 2)
      taille = 5;
      else taille = 3;

    if (variable_partie->num_joueur == 1) {

      Pions_joueur joueur1 = {  TAILLE_PLATEAU - 1, TAILLE_PLATEAU, // Données des coordonnées x
                                TAILLE_PLATEAU - taille, TAILLE_PLATEAU,  // Données des coordonnées y
                                1, -1 // Données nécessaire au if de fin_joueur
                              };

      fin_joueur(&joueur1, variable_partie);

    } else if (variable_partie->num_joueur == 2) {

      Pions_joueur joueur2 = {  0, taille,  // Données des coordonnées x
                                0, taille,  // Données des coordonnées y
                                0, -1 // Données nécessaire au if de fin_joueur
                              };

      fin_joueur(&joueur2, variable_partie);

    } else if (variable_partie->num_joueur == 3 ) {

      Pions_joueur joueur3 = {	0, 1,  // Données des coordonnées x
                                TAILLE_PLATEAU - taille, TAILLE_PLATEAU,  // Données des coordonnées y
                                0, 1  // Données nécessaire au if de fin_joueur
                              };

      fin_joueur(&joueur3, variable_partie);

    } else if (variable_partie->num_joueur == 4 ) {

      Pions_joueur joueur4 = {  TAILLE_PLATEAU - taille, TAILLE_PLATEAU,	// Données des coordonnées x
                                0, taille,  // Données des coordonnées y
                                1, 1  // Données nécessaire au if de fin_joueur
                              };

      fin_joueur(&joueur4, variable_partie);
    }
    return 0;
}

int lancement_partie(DonneesPartie *variable_partie)  // Lance la partie
{

    do // Boucle pour rejouer tant que la partie n'est pas finie
    {
      variable_partie->num_joueur = joueur_suivant(variable_partie->nombre_joueur,
                                  variable_partie->num_joueur,
                                  variable_partie->classement);

      deroulement_tour(variable_partie);
      sauvegarde(variable_partie);
    } while(fin_partie(variable_partie) == 0);

    // Supression du fichier de sauvegarde
    #ifdef linux
      system("rm partie.save");
    #elif _WIN32
      system("del partie.save");
    #endif

    // Fin du jeu

    afficher_plateau(variable_partie->plateau);
    printf("Jeu termine !\n\n");
    afficher_classement(variable_partie->classement,variable_partie->nombre_joueur);  // Affichage du classement

    return 0;
}

int fin_partie(DonneesPartie *variable_partie)  // Détermine le moment où la pratie s'arrête
{

  int i, test = 0;

  for (i = 0; i < variable_partie->nombre_joueur; i++) // On test pour tous les joueurs qui jouent
  {
    if (variable_partie->classement[i] != 0)
      test ++; // Le tableau classement contient un ou des joueurs
  }

  if (test == variable_partie->nombre_joueur)
    return 1; // Si test est égal au nombre de joueurs alors on a TOUT nos joueurs dans le tableau classement et il faut stopper la partie

  return 0;
}
