#include "utilitaire.h"

int choix_nombre_joueur()
{
    int nombre_joueur;
    do
    {
        printf("Entrez le nombre de joueur (2 ou 4): ");
        if(scanf("%d", &nombre_joueur) != 1) // Test si la valeur est un entier
            vider_buffer();

    } while (nombre_joueur != 2  && nombre_joueur != 4); // Test si l'entre est valide
    printf("\nVous avez choisi %d joueurs\n\n", nombre_joueur);
    return nombre_joueur;

}

void vider_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void clear_console()
{
    #ifdef linux    // Si on est sur linux
        system("clear");
    #elif _WIN32    // Sinon si on est sur windows
        system("cls");
    #endif
}

void afficher_plateau(const int plateau[][TAILLE_PLATEAU])
{
    int x,y,i;

    printf(" ###### PLATEAU ######\n\n");
    printf("  ");
    for (i = 0 ; i < TAILLE_PLATEAU ; i++)
    {
        printf(" %d",i);  // affichage coordonnee en abscisse
    }

    printf("\n  ");

    for (i = 0 ; i < TAILLE_PLATEAU ; i++)
    {
        printf(" -");  // decoration
    }

    printf("\n");

    for(y = 0; y < TAILLE_PLATEAU ; y++)
    {
        printf("%d| ",y); // affichage coordonnee en ordonnee
        for(x = 0; x < TAILLE_PLATEAU ; x++)
        {
            printf("%d ",plateau[x][y]); // affichage valeur du tableau
        }
        printf("\n");
    }
    printf("\n");
}

void afficher_classement(const int classement[4],int nombre_joueur)
{
    int i;

    printf(" ##### CLASSEMENT ######\n\n");

    for(i = 0; i<nombre_joueur; i++)
    {
        printf("%d) JOUEUR %d\n",i+1,classement[i]);
    }
    printf("\n");

}

void generation_pions(int taille, int y_debut, int y_fin, int x_debut, int x_fin, int numero_joueur, int plateau[][TAILLE_PLATEAU])
{
    int x, y;

    for (y = y_debut; y <= y_fin; y ++) //y signifit les ordonnées dans notre PLATEAU
    {

        for (x = x_debut; x <= x_fin; x++) //  x signifit les abscisses dans notre PLATEAU
        {

            plateau [x][y] = numero_joueur; // on change la valeur du PLATEAU
        }

        // on fait différentes incrémentations / décrémentations en fonction du joueur pour que les pions soient à la bonne place
        if (numero_joueur == 1)
            x_fin --;

        else if (numero_joueur == 2)
            x_debut --;

        else if (numero_joueur == 3)
            x_debut ++;

        else if (numero_joueur == 4)
            x_fin ++;
    }
}

void generation_terrain(int nombre_joueur,  int plateau[][TAILLE_PLATEAU])
{
    int taille;

    // initialisation d'une variable taille pour savoir la taille de nos pyramides de pions
    if (nombre_joueur == 2)
        taille = 5;
    else taille = 3;

    // soit on passe 9 en paramètre soit on passe _TAILLE_PLATEAU_ -1 en paramètre : c'est au choix

    generation_pions(taille, 0, taille, 0, taille - 1, 1, plateau);
    generation_pions(taille, 9 - (taille - 1), 9, 9 , 9, 2, plateau);

    if (nombre_joueur == 4) {

        generation_pions(taille, 0, taille - 1, 9 - (taille - 1), 9, 3, plateau);
        generation_pions(taille, 9 - (taille - 1), 9, 0, taille - 3, 4, plateau);
    }
}
