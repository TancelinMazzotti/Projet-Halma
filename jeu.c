#include "jeu.h"

int test_emplacement(int valeur_emplacement, int x, int y, int plateau[][TAILLE_PLATEAU]) // Test la valeur de l'emplacement du plateau
{
    if (((x >= 0 && x < TAILLE_PLATEAU) && (y >= 0 && y < TAILLE_PLATEAU)) && plateau[x][y] == valeur_emplacement)  // Test si la valeur de la case correspond à la valeur que l'on a passé en parramètre
        return 1;
    else return 0;
}

void selection_coordonne(int tableau_coord[2])  // Demande les valeurs et remplis le tableau [X;Y]
{
    do
    {
        printf("Entrez coordonnee X: ");
        if(scanf("%d",&tableau_coord[0]) != 1) // On demande l'abscisse
            vider_buffer();
    } while (tableau_coord[0] < 0 || tableau_coord[0] >= TAILLE_PLATEAU); // Test si la saisie est correcte sinon on recommence la saisie

    do
    {
        printf("Entrez coordonnee Y: ");
        if(scanf("%d",&tableau_coord[1]) != 1) // On demande l'ordonnée
            vider_buffer();
    } while (tableau_coord[1] < 0 || tableau_coord[1] >= TAILLE_PLATEAU); // Test si la saisie est correcte sinon on recommence la saisie
}

int deplacer_pion(DonneesPartie *variable_partie) // Permet le déplacement d'un pion
{
  int i = 0;
  for(i = 0; i < variable_partie->taille_tableau_destination ; i++)
  {
    if (variable_partie->coord_destination_pion[0] == variable_partie->tableau_destination[i][0] && variable_partie->coord_destination_pion[1] == variable_partie->tableau_destination[i][1])
    {
      variable_partie->plateau[variable_partie->coord_destination_pion[0]][variable_partie->coord_destination_pion[1]] = variable_partie->num_joueur; // Le pion arrive sur la case de destination
      variable_partie->plateau[variable_partie->coord_pion_selectionner[0]][variable_partie->coord_pion_selectionner[1]] = 0; // Libère l'emplacement d'où vient le pion

      return 1;
    }
  }
  return 0;
}

int joueur_suivant(int nombre_joueur, int numero_joueur, int classement[])  // Retourne le numero du joueur suivant (MIN = 1 & MAX = 4)
{
    int i,j,cpt = 0,fini = 0;
    numero_joueur++;
    if (numero_joueur > nombre_joueur)  // Vérifit si l'on ne dépasse pas le nombre de joueur de la partie
        numero_joueur = numero_joueur - nombre_joueur;  // On revient au premier joueur

    for (i = 0; i < nombre_joueur ; i++)  // Parcours tout les joueurs
    {
        cpt = numero_joueur + i;  // Mémerise le numéro du joueur suivant
        if (cpt > nombre_joueur)  // Vérifit si l'on ne dépasse pas le nombre de joueur de la partie
            cpt = cpt - nombre_joueur;  // On revient au premier joueur

        for (j = 0; j < nombre_joueur; j++) // Parcours tout les joueurs
        {
            if (classement[j] == cpt) // Regarde si le joueur a déjà fini de jouer
                fini = 1;
        }
        if(fini == 0) // Test si le joueur à fini
            return cpt; // On dit que c'est à ce joueur de jouer
        else fini = 0;  // On réinitialise la variable fini et on test le joueur suivant
    }

    return 0; // Tous les joueurs ont fini
}

void generation_classement(DonneesPartie *variable_partie) // Remplis le tableau du classement
{
  int i, total;

  if (variable_partie->nombre_joueur == 2) // La variable total sert à savoir quel joueur on ajoute quand tous les joueurs sauf un ont fini
    total = 3;
    else total = 10;

  for (i = 0; i < variable_partie->nombre_joueur; i++) {
    if (variable_partie->classement[i] == 0)  // Si le tableau ne contient pas de valeur on le remplit avec le numéro du joueur
    {
      variable_partie->classement[i] = variable_partie->num_joueur;

      if (variable_partie->classement[variable_partie->nombre_joueur - 2] != 0) // On regarde si on a mis l'avant dernier joueur dans le tableau pour ajouter le dernier
      {
        variable_partie->classement[variable_partie->nombre_joueur - 1] = total - somme_classement(variable_partie);  // On ajoute le joueur qui n'a pas fini
      }

    break;
    }
  }
}

int somme_classement(DonneesPartie *variable_partie)  // Fait la somme des valeurs de toutes les cases du tableau classement
{
  int i, somme = 0;

  for (i = 0; i < variable_partie->nombre_joueur - 1; i++) {
    somme += variable_partie->classement[i];  // On calcul la somme de toutes les cases du tableau
  }

  return somme;
}

void fin_joueur(Pions_joueur *fin, DonneesPartie *variable_partie)  // Test si le joueur x a fini
{
    int x, y, test = 0;

    for (y = fin->y_debut; y < fin->y_fin; y ++) // y signifit les ordonnées dans notre PLATEAU
    {
        for (x = fin->x_debut; x < fin->x_fin; x++) // x signifit les abscisses dans notre PLATEAU
        {
          if (variable_partie->plateau[x][y] != variable_partie->num_joueur) // On test si les pions du joueur sont bien sur les emplacements pour qu'il ait fini
              test ++;
        }

        if (fin->modification == 0)		// On fait différentes incrémentations / décrémentations en fonction du joueur pour tester nos pyramides de pions

            fin->x_fin += fin->incrementation_x;

        else fin->x_debut += fin->incrementation_x;
    }
    if (test == 0) // si test = 0 alors le joueur à fini
      generation_classement(variable_partie);
}



int recherche_valeur_tableau(int **tableau,int taille, int coord_x, int coord_y) // Vérifit si l'on avait déjà trouvé la destination auparavant
{
  int i = 0;
  for (i = 0; i < taille; i++)  // On parcours le tableau
  {
    if (tableau[i][0] == coord_x && tableau[i][1] == coord_y) // Test si les coordonées sont déjà dans le tableau
      return 0;
  }
  return 1; // Les coordonées ne sont pas dans le tableau
}

void recherche_destination( DonneesPartie *variable_partie, int coord_selectionner[2], int deplacement) // Cherche les destinations possibles autour d'une coordonnée (en sautant un pion ou non)
{
  int y,x; // variable de boucle
  int destination_x; // abscisse de coordonne de destiantion
  int destination_y; // ordonnnee de coordonne de destination
  int ecart_x = 0; // ecart en abscisse  si on fait un saut
  int ecart_y = 0; // ecart en ordonnnee si on fait un saut

  // Test sans sauter
  for (y = -1*deplacement; y <= deplacement; y+=deplacement) // Parcour grille en ordonnnee
  {
    destination_y = coord_selectionner[1]+y; // calcul coordonne y destination
    if (destination_y >= 0 && destination_y < TAILLE_PLATEAU) // test si on dépasse pas le tableau en y
    {
      for (x = -1*deplacement; x <= deplacement; x+=deplacement) // Parcours grille en abscisse
      {
        destination_x = coord_selectionner[0]+x; // calcul coordonne x destination
        if (destination_x >= 0 && destination_x < TAILLE_PLATEAU) // test si on dépasse pas le tableau en x
        {
          if (deplacement == 2)
          {
            // Calcul coordonnee de l'obstacle
            ecart_x = coord_selectionner[0] - destination_x;
            ecart_y = coord_selectionner[1] - destination_y;

              //abscisse
            if (ecart_x > 0)
                ecart_x = ecart_x - 1;
            else if (ecart_x < 0)
                ecart_x = ecart_x + 1;
              //ordonnnee
            if (ecart_y > 0)
                ecart_y = ecart_y - 1;
            else if (ecart_y < 0)
                ecart_y = ecart_y + 1;
          }

          // Test si la destiantion et vide et ( si il y a un obstacle ou on se deplace sans sauter)
          if (variable_partie->plateau[destination_x][destination_y] == 0
                &&
              (variable_partie->plateau[destination_x + ecart_x][destination_y + ecart_y] != 0 || deplacement == 1)
             )
          {
            // Test si la coordonnee n'a pas ete trouve avant
            if (recherche_valeur_tableau(variable_partie->tableau_destination, variable_partie->taille_tableau_destination,destination_x,destination_y))
            {
              variable_partie->taille_tableau_destination = variable_partie->taille_tableau_destination+1; // On agrandie la taille du tableau
              variable_partie->tableau_destination = (int**)realloc(variable_partie->tableau_destination, variable_partie->taille_tableau_destination * sizeof(int*)); // On realoue la memoire
              variable_partie->tableau_destination[variable_partie->taille_tableau_destination -1 ] = malloc(2 * sizeof(int)); // On ralloue la memoire
              variable_partie->tableau_destination[variable_partie->taille_tableau_destination -1 ][0] = destination_x; // On ajoute au tableau la destination en abscisse
              variable_partie->tableau_destination[variable_partie->taille_tableau_destination -1 ][1] = destination_y; // On ajoute au tableau la destination en ordonnee

            }
          }
        }
      }
    }
  }
}

void prevision(DonneesPartie *variable_partie)  // Prévoit toutes les destinations possibles d'un pion
{
  /* On sécurise le tableau */

  variable_partie->taille_tableau_destination = 0;  // On réinitialise la taille du tableau à 0
  free(variable_partie->tableau_destination); // On libère la mémoire du tableau
  variable_partie->tableau_destination = NULL;  // On initialise le pointeur à NULL
  variable_partie->tableau_destination = malloc(0 * sizeof(int*));  // On recréer un tableau de taille 0

  int i = 0;

  recherche_destination(variable_partie,variable_partie->coord_pion_selectionner,2);  // On recherche les destinations qui nécessitent un saut

  for(i = 0 ; i < variable_partie->taille_tableau_destination; i++) // On parcours l'intégralité des destinations trouvées précédement
  {
    recherche_destination(variable_partie,variable_partie->tableau_destination[i],2); // On regarde si l'on peut encore sauter après
  }

  recherche_destination(variable_partie,variable_partie->coord_pion_selectionner,1);  // On recherche les destinations qui ne nécessitent pas un saut

  for (i = 0; i < variable_partie->taille_tableau_destination ; i++)  // On parcours toutes les destinations trouvées
  {
    variable_partie->plateau[variable_partie->tableau_destination[i][0]][variable_partie->tableau_destination[i][1]] = 5; // On écrit sur le plateau les sauts possibles
  }

}
