#include "utilitaire.h"
#include "partie.h"

int main()
{
    int recommencer;

    do
    {
        clear_console();
        printf("\n ***** HALMA GAME ***** by Tancelin MAZZOTTI & Camille LANGE\n\n");
        lancement_partie();
        do
        {
            printf("Voulez-vous recommencer le jeu ? (1 = oui et 0 = non): ");
            if(scanf("%d", &recommencer) != 1) // Test si la valeur est un entier
                vider_buffer();

        } while (recommencer != 0  && recommencer != 1); // Test si l'entre est valide
    }while(recommencer);

    return 0;
}
