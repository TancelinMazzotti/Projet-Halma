#include "partie.h"

int deroulement_tour(struct Partie * variable_partie)
{
    do
    {
        clear_console();
        afficher_plateau(variable_partie->plateau);
        printf("JOUEUR %d a vous de jouer ! \n\n",variable_partie->num_joueur);

        if (variable_partie->pion_sauter == 0) // empeche le joueur de changer de pion si il a deja fait un saut
        {
            printf("Selectionner un pion\n");
            selection_coordonne(variable_partie->coord_pion_selectionner); // Selection pion
        }

        printf("Selectionner destination\n");
        selection_coordonne(variable_partie->coord_destination_pion); // Selection destinantion du pion

        // deplacer_pion sera un peu modifier par la suite
        variable_partie->resultat_deplacement = deplacer_pion(variable_partie);

        clear_console();
        afficher_plateau(variable_partie->plateau);

        // Affichage information sur le deplacemnt effectue (faire une fonction affichage)
        if(variable_partie->resultat_deplacement == 0)
            printf("\nERREUR: Deplacemnt impossible\n\n");
        else if(variable_partie->resultat_deplacement == 1)
            printf("\nDeplacemnt standard reussie\n\n");
        else if (variable_partie->resultat_deplacement == 2)
            printf("\nDeplacement en sautant un pion reussie\n\n");


        // Demande fin du tour en focntion du resultat du deplacemnt (a modifier avec fonction et parametre)
        if(variable_partie->resultat_deplacement != 1)
            if(demande_fin_tour() == 1)
                variable_partie->resultat_deplacement = 1;

    }while (variable_partie->resultat_deplacement != 1); // Tant que le deplacement n'est pas valide

    /* test victoire et retourne la valeur du test (idee) */
    return 0;
}

int lancement_partie()
{
    // Initialisation de la structure
    struct Partie variable_partie = {0,0,{0},{0},{0},{0},0,0};

    variable_partie.nombre_joueur = choix_nombre_joueur();
    generation_terrain(variable_partie.nombre_joueur, variable_partie.plateau);

    /*** Faire une boucle tant que tout les joueur n'ont pas fini ***/
    variable_partie.num_joueur = joueur_suivant(variable_partie.nombre_joueur,
                                variable_partie.num_joueur,
                                variable_partie.classement); // le num_joueur passe a 1

    deroulement_tour(&variable_partie);
    /*****************************************************************/

    // fin du jeu
    afficher_plateau(variable_partie.plateau);
    printf("Jeu termine !\n\n");
    afficher_classement(variable_partie.classement,variable_partie.nombre_joueur);

    return 0;
}
