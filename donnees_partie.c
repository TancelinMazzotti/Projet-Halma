#include "donnees_partie.h"

int char_to_int(char chiffre)	// Convertisseur char en int
{
	int converstion = chiffre -'0';
	return converstion;
}
char int_to_char(int chiffre)	// Convertisseur int en char
{
	char converstion = chiffre +'0';
	return converstion;
}


int sauvegarde(DonneesPartie *donnes_a_sauvegarder)	// sauvegarde la partie
{
    FILE * fichier_sauvegarde = NULL;
    fichier_sauvegarde = fopen("partie.save","w"); // Ouverture du fichier de suavegarde
		int x,y,i;

    if(fichier_sauvegarde != NULL)	// Test si le fichier a été correctement ouvert
    {
        for (y = 0; y < TAILLE_PLATEAU; y++)	// Boucles imbriquées (double for) qui parcourent toutes les cases du tableau
        {
        	for (x = 0; x < TAILLE_PLATEAU; x++)
        	{
        		fprintf(fichier_sauvegarde,"%c",int_to_char(donnes_a_sauvegarder->plateau[x][y])); // Sauvegarde les cases du plateau
        	}
            fprintf(fichier_sauvegarde,"\n"); // Passage de ligne
        }

        fprintf(fichier_sauvegarde,"%c\n%c\n",int_to_char(donnes_a_sauvegarder->num_joueur), // Sauvegarde numero de joueur
        									int_to_char(donnes_a_sauvegarder->nombre_joueur)); // Sauvegarde nombre de joueur

        for (i = 0; i < 4; i++)
        {
        	fprintf(fichier_sauvegarde, "%c",int_to_char(donnes_a_sauvegarder->classement[i]) ); // sauvegarde classement
        }

        fclose(fichier_sauvegarde); // fermeture du fichier de sauvegarde
        return 1;
    }

    else	// Le fichier n'a pas pu être correctement ouvert
    {
        printf("Erreur ouverture de fichier sauvegarde\n");
        return 0;
    }
}

int charger(DonneesPartie *donnees_a_charger)	// Chargement de la derniere sauvegarde
{
    FILE * fichier_chargement = NULL;
    fichier_chargement = fopen("partie.save","r"); // Ouverture du fichier de chargement
		int x,y,i;
    if (fichier_chargement != NULL)
    {
			for (y = 0; y < TAILLE_PLATEAU; y++)	// Boucles imbriquées (double for) qui parcourent toutes les cases du tableau
			{
				for (x = 0; x < TAILLE_PLATEAU; x++)
				{
					donnees_a_charger->plateau[x][y] = char_to_int(fgetc(fichier_chargement)); // Chargement plateau dans la structure
				}
				fgetc(fichier_chargement); // Passage de ligne dans le fichier
			}
			donnees_a_charger->num_joueur = char_to_int(fgetc(fichier_chargement)); // Chargement numero de joueur
			fgetc(fichier_chargement); // Passage de ligne dans le fichier
			donnees_a_charger->nombre_joueur = char_to_int(fgetc(fichier_chargement)); // Chargement nombre de joueur
			fgetc(fichier_chargement); // Passage de ligne dans le fichier
			for (i = 0; i < 4; i++)
			{
				donnees_a_charger->classement[i] = char_to_int(fgetc(fichier_chargement)); // Chargement classement
			}

      fclose(fichier_chargement); // Fermeture du fichier de chargement
      return 1;
    }

    else	// Le fichier n'a pas pu être correctement ouvert
    {
        return 0;
    }
}
