#include "jeu.h"

int test_emplacement(int valeur_emplacement, int x, int y, const int plateau[][TAILLE_PLATEAU])
{
    if (((x >= 0 && x < TAILLE_PLATEAU) && (y >= 0 && y < TAILLE_PLATEAU)) && plateau[x][y] == valeur_emplacement)
        return 1;
    else return 0;
}

void selection_coordonne(int tableau_coord[2])
{
    do
    {
        printf("Entrez coordonnee X: ");
        if(scanf("%d",&tableau_coord[0]) != 1)
            vider_buffer();
    } while (tableau_coord[0] < 0 || tableau_coord[0] >= TAILLE_PLATEAU);

    do
    {
        printf("Entrez coordonnee Y: ");
        if(scanf("%d",&tableau_coord[1]) != 1)
            vider_buffer();
    } while (tableau_coord[1] < 0 || tableau_coord[1] >= TAILLE_PLATEAU);
}

int deplacer_pion(int num_joueur,int coord_pion[], int coord_destination[], int plateau[][TAILLE_PLATEAU],int *pion_sauter)
{
    int ecart_x = coord_destination[0] - coord_pion[0];
    int ecart_y = coord_destination[1] - coord_pion[1];

    if (ecart_x == 0 && ecart_y == 0)
        return 0;


    // Deplacement sans sauter de pion
    if ( (ecart_x < 2 && ecart_y < 2) && (ecart_x > -2 && ecart_y > -2))
    {
        if (*pion_sauter == 0)
        {
            printf("Deplacer sans sauter de pion\n");
            if(test_emplacement(0, coord_destination[0],coord_destination[1], plateau) == 1)
            {
                plateau[coord_destination[0]][coord_destination[1]] = num_joueur;
                plateau[coord_pion[0]][coord_pion[1]] = 0;
                return 1;
            }
        }
    }

    // Deplacement sauter pion
    else if ( ((ecart_x < 3 && ecart_y < 3) && (ecart_x > -3 && ecart_y > -3)) && ((ecart_x != 1 && ecart_x != -1) && (ecart_y != 1 && ecart_y != -1)))
    {
        // Calcul coordonne obstacle
        if (ecart_x > 0)
            ecart_x = ecart_x - 1;
        else if (ecart_x < 0)
            ecart_x = ecart_x + 1;

        if (ecart_y > 0)
            ecart_y = ecart_y - 1;
        else if (ecart_y < 0)
            ecart_y = ecart_y + 1;

        if (test_emplacement(0, coord_pion[0] + (ecart_x),coord_pion[1] + (ecart_y), plateau) == 0)
        {
            plateau[coord_destination[0]][coord_destination[1]] = num_joueur;
            plateau[coord_pion[0]][coord_pion[1]] = 0;
            *pion_sauter = 1;
            return 2;
        }

    }
    return 0;
}

int joueur_suivant(const int nombre_joueur, int numero_joueur, const int classement[])
{
    int i,j,cpt = 0,fini = 0;
    numero_joueur++;
    if (numero_joueur > nombre_joueur)
        numero_joueur = numero_joueur - nombre_joueur;

    for (i = 0; i < nombre_joueur ; i++)
    {
        cpt = numero_joueur + i;
        if (cpt > nombre_joueur)
            cpt = cpt - nombre_joueur;

        for (j = 0; j < nombre_joueur; j++)
        {
            if (classement[j] == cpt)
                fini = 1;
        }
        if(fini == 0)
            return cpt;
        else fini = 0;
    }

    return 0;
}

int demande_fin_tour()
{
    int continuer;
    do
    {
        printf("Voulez-vous mettre fin a votre tour ? (1 = oui et 0 = non): ");
        if(scanf("%d", &continuer) != 1) // Test si la valeur est un entier
            vider_buffer();

    } while (continuer != 0  && continuer != 1); // Test si l'entre est valide
    return continuer;
}
