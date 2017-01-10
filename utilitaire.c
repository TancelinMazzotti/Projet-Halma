#include "utilitaire.h"

void clear_console()  // Vide la console
{
    #ifdef linux  // Si on est sur linux
        system("clear");
    #elif _WIN32  // Si on est sur windows
        system("cls");
    #endif
}

int choix_nombre_joueur() // Demande le nombre de joueur
{
    int nombre_joueur;

    clear_console();

    do
    {
        printf("Entrez le nombre de joueur (2 ou 4): ");
        if(scanf("%d", &nombre_joueur) != 1) // Test si la valeur est un entier
            vider_buffer();

    } while (nombre_joueur != 2  && nombre_joueur != 4); // Test si l'entre est valide

    printf("\nVous avez choisi %d joueurs\n\n", nombre_joueur);

    return nombre_joueur; // Retourne le nombre de joueur sélectionné

}

void vider_buffer() // Vide le buffer pour le scanf
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void afficher_plateau(int plateau[][TAILLE_PLATEAU])  // Affiche le plateau
{
    int x,y,i;

    printf("\n ###### PLATEAU ######\n\n");
    printf("\\X");
    for (i = 0 ; i < TAILLE_PLATEAU ; i++)
    {
        printf(" %d",i);  // Affichage des coordonnées en abscisse
    }

    printf("\nY ");

    for (i = 0 ; i < TAILLE_PLATEAU ; i++)
    {
        printf(" -"); // Décoration
    }

    printf("\n");

    for(y = 0; y < TAILLE_PLATEAU ; y++)
    {
        printf("%d| ",y); // Affichage des coordonnées en ordonnée
        for(x = 0; x < TAILLE_PLATEAU ; x++)
        {
          switch (plateau[x][y])
          {
            case 0 : printf("\033[37m%d \033[0m",plateau[x][y]); // Affichage valeur du tableau blanc
                     break;

            case 1 : printf("\033[31m%d \033[0m",plateau[x][y]); // Affichage valeur du tableau rouge
                     break;

            case 2 : printf("\033[36m%d \033[0m",plateau[x][y]); // Affichage valeur du tableau cyan
                     break;
            case 3 : printf("\033[32m%d \033[0m",plateau[x][y]); // Affichage valeur du tableau vert
                     break;
            case 4 : printf("\033[33m%d \033[0m",plateau[x][y]); // Affichage valeur du tableau jaune
                     break;
            case 5 : plateau[x][y] = 0;
                     printf("\033[35m%d \033[0m",plateau[x][y]); // Affichage valeur du tableau violet
                     break;
            default : printf("Mauvaise valeur dans le plateau\n");  // En cas de valeur du tableau erronée
                      break;
          }
        }
        printf("\n");
    }
    printf("\n");
}

void afficher_classement(int classement[4],int nombre_joueur) // Affiche le classement
{
    int i;

    printf(" ##### CLASSEMENT ######\n\n");

    for(i = 0; i<nombre_joueur; i++)  // Parcourt tout le tableau classement
    {
        printf("%d) JOUEUR %d\n",i+1,classement[i]);  // Affiche le classement
    }
    printf("\n");

}

void generation_pions(Pions_joueur *pions, DonneesPartie *variable_partie, int numero_joueur) // Place les pions d'un joueur à son emplacement de départ
{
    int x, y;

    for (y = pions->y_debut; y < pions->y_fin; y ++) // y signifit les ordonnées dans notre PLATEAU
    {

        for (x = pions->x_debut; x < pions->x_fin; x++) // x signifit les abscisses dans notre PLATEAU
        {

            variable_partie->plateau [x][y] = numero_joueur; // On change la valeur du PLATEAU
        }

        if (pions->modification == 0)	// On fait différentes incrémentations / décrémentations en fonction du joueur pour placer les pions en pyramide

            pions->x_fin += pions->incrementation_x;

        else pions->x_debut += pions->incrementation_x;
    }
}

void generation_terrain(DonneesPartie *variable_partie) //Place les pions de tous les joueurs aux bons emplacements au départ de la partie
{
    int taille;

    // Initialisation d'une variable taille pour savoir la taille de nos pyramides de pions
    if (variable_partie->nombre_joueur == 2)
      taille = 5;
      else taille = 3;

    // Parallélisation de la génération des pions
    #pragma omp parallel sections   // Sections à traiter en parallèle
    {
        #pragma omp section // Processus génération des pions du joueur 1
        {
            printf("[INFO] Generation des pions du joueur 1 par le thread: %d\n",omp_get_thread_num() );
            Pions_joueur pions_1 = {    0, taille,  // Données des coordonnées x
                                        0, taille,  // Données des coordonnées y
                                        0, -1 // Données nécessaire au if de generation_pions
                                    };
            generation_pions(&pions_1, variable_partie, 1);
        }

        #pragma omp section // Processus génération des pions du joueur 2
        {
            printf("[INFO] Generation des pions du joueur 2 par le thread: %d\n",omp_get_thread_num() );
            Pions_joueur pions_2 = {    TAILLE_PLATEAU - 1, TAILLE_PLATEAU, // Données des coordonnées x
                                        TAILLE_PLATEAU - taille, TAILLE_PLATEAU,  // Données des coordonnées y
                                        1, -1 // Données nécessaire au if de generation_pions
                                    };
            generation_pions(&pions_2, variable_partie, 2);
        }

        #pragma omp section // Processus génération des pions du joueur 3
        {
            if (variable_partie->nombre_joueur == 4) // On ne génère pas si on a pas choisi 4 joueurs
            {
              printf("[INFO] Generation des pions du joueur 3 par le thread: %d\n",omp_get_thread_num() );
            	Pions_joueur pions_3 = { TAILLE_PLATEAU - taille, TAILLE_PLATEAU,  // Données des coordonnées x
                                       0, taille, // Données des coordonnées y
                                       1, 1 // Données nécessaire au if de generation_pions
        				                     };
              generation_pions(&pions_3, variable_partie, 3);
            }
        }

        #pragma omp section // Processus génération des pions du joueur 4
        {
            if (variable_partie->nombre_joueur == 4) // On ne génère pas si on a pas choisi 4 joueurs
            {
              printf("[INFO] Generation des pions du joueur 4 par le thread: %d\n",omp_get_thread_num() );
            	Pions_joueur pions_4 = {  0, 1, // Données des coordonnées x
                                        TAILLE_PLATEAU - taille, TAILLE_PLATEAU,  // Données des coordonnées y
                                        0, 1  // Données nécessaire au if de generation_pions
                				             };

              generation_pions(&pions_4, variable_partie, 4);
            }
        }
    }
    clear_console();
}
