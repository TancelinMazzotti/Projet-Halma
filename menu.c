#include "menu.h"

void afficher_menu()  // Affiche le menu
{
  clear_console();

  /* Titre principal */

  printf("\n _   _       _                   _____                      \n");
  printf("| | | |     | |                 |  __ \\                      \n");
  printf("| |_| | __ _| |_ __ ___   __ _  | |  \\/ __ _ _ __ ___   ___  \n");
  printf("|  _  |/ _` | | '_ ` _ \\ / _` | | | __ / _` | '_ ` _ \\ / _ \\ \n");
  printf("| | | | (_| | | | | | | | (_| | | |_\\ \\ (_| | | | | | |  __/ \n");
  printf("\\_| |_/\\__,_|_|_| |_| |_|\\__,_|  \\____/\\__,_|_| |_| |_|\\___| \n");

  printf("\n\nby Tancelin MAZZOTTI & Camille LANGE\n\n");

  /* Menu */

  printf("************* MENU ***************\n");
  printf("* 1 : Lancer une nouvelle partie *\n");
  printf("* 2 : Charger la dernière partie *\n");
  printf("* 3 : Lire les règles            *\n");
  printf("* 4 : Quitter                    *\n");
  printf("**********************************\n\n");
}

void menu ()  // Menu d'acceuil
{
  int choix;

  // Initialisation de la structure nécessaire à notre partie
  DonneesPartie variable_partie = {0,0,{{0}},{0},{0},{0},0,NULL,0};

  afficher_menu();

  do {  // Choix sécurisé

    printf("Que choisisez vous ? ");
    if(scanf("%d", &choix) != 1) // Test si la valeur est un entier
        vider_buffer();

  } while(choix != 1 && choix != 2 && choix != 3 && choix != 4);

  /* Test pour savoir ce que l'utilisateur veut faire */

  switch (choix)
  {
    case 1 : // Lancement d'une nouvelle partie
             variable_partie.nombre_joueur = choix_nombre_joueur();  // On créer un nouveau terrain
             generation_terrain(&variable_partie);

             lancement_partie(&variable_partie);
             recommencer(&variable_partie);
             break;

    case 2 : // Chargement de la dernière partie jouée
             if(charger(&variable_partie) != 0)  // Test de la présence d'un fichier de chargement valide
              {
                clear_console();
                lancement_partie(&variable_partie);
                recommencer(&variable_partie);
              }
             else
              {
                clear_console();
                menu();
                printf("Erreur ouverture de fichier sauvegarde\n"); // Message d'erreur en cas de mauvais fichier de chargement
              }
              break;

    case 3 : // Exposé des règles du jeu + retour au menu
             regles();
             menu();
             break;

    case 4 : // On quitte le programme
             clear_console();
             break;

    default : // En cas de problème dans le tri sécurisé du dessus
              printf("Mauvaise Sélection dans le menu\n");
              break;
  }
}

void regles() // Affiche les règles du jeu
{
  clear_console();

  printf("\n ***** HALMA GAME *****\n\n");
  printf("Le Halma est un jeu de plateau qui peut s'apparenter aux Dames Chinoise classique.\n");
  printf("A un détail près : le plateau est carré, ce qui rend les cases carrées et non hexagonales.\n\n");
  printf("Le but du jeu est donc de déplacer tous ces pions à l'opposé du plateau. De son camp vers le camp du joueur en face.\n\n");
  printf("A chaque tour d'un joueur il peut donc déplacer un de ces pions, 2 types de mouvements sont autorisés : \n");
  printf("- Soit le pion ne se déplace que d'une seule case sans rencontrer d'autres pions.\n");
  printf("- Soit le pion saute un autre pion et donc se déplace de 2 cases.\n\n");
  printf("NOTE : Après s'être déplacé en sautant un pion, le joueur peut (s'il le souhaite) recommencer et sauter un autre pion. Et ainsi de suite jusqu'à ce qu'il ne puisse plus sauter de pions. Mais il n'a pas le droit de faire un déplacement sans sauter de pion.\n\n");
  printf("Le Halma peut se jouer à 2 ou 4 joueurs.\n\n");
  printf("Lorsque vous allez sélectioner un pion, ces déplacements possibles (pour ce tour) s'afficheront en violet. Vous n'avez qu'à écrire les coordonnées de l'endroit où vous voulez qu'il arrive pour le déplacer (pas besoin de faire les sauts intermédiaires).\n");
  printf("Bonne chance !\n");

  printf("Appuyez sur entrée pour quitter et revenir au menu\n");
  vider_buffer();
  while(getchar() != '\n'); // On "met en pause" le temps que l'utilisateur puisse lire les règles
}

void recommencer(DonneesPartie *variable_partie)  // Demande si l'utilisateur veux recommencer le jeu
{
  int recommencer;

  do  // Test sécurisé
  {
      printf("\nVoulez-vous retourner au menu ? (1 = oui et 0 = non): ");
      if(scanf("%d", &recommencer) != 1) // Test si la valeur est un entier
        vider_buffer();
      if (recommencer == 1) {
        menu();
      }
  } while (recommencer != 0  && recommencer != 1); // Test si l'entre est valide
}
