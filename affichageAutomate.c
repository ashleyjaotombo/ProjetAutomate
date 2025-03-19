#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichageAutomate.h"

char*** creationAutomate(int nbEtats, int *entree, int *sortie, char** TableauTransition, int nbTransitions) {
  // Allocation du tableau pour l'automate
  char ***automate = (char***)malloc((nbEtats + 1) * sizeof(char*));

  // Initialisation des lignes du tableau de l'automate
  for (int i = 0; i <= nbEtats; i++) {
    automate[i] = malloc(5 * sizeof(char*)); // 5 colonnes
    for (int j = 0; j < 5; j++) {
      automate[i][j] = (char*)calloc(50, sizeof(char)); // Chaque cellule peut contenir une chaîne de 50 caractères
    }
  }

  // Compléter les titres des colonnes
  strcpy(automate[0][0], " ");
  strcpy(automate[0][1], "Etat");
  strcpy(automate[0][2], "a");
  strcpy(automate[0][3], "b");
  strcpy(automate[0][4], "c");

  // Compléter les états avec les informations sur les entrées et sorties
  for (int i = 1; i <= nbEtats; i++) {
    // Vérification des états d'entrée et de sortie
    if (entree[i-1] == 1) {
      strcpy(automate[i][0], "E");
    }
    if (sortie[i-1] == 1) {
      strcat(automate[i][0], "S");
    }
    sprintf(automate[i][1], "%d", i); // Remplir la colonne de l'état
  }

  // Compléter les transitions dans l'automate
  for (int i = 0; i < nbTransitions; i++) {
    // Détacher les informations de la transition
    int etatSource, etatDest;
    char symbole;
    sscanf(TableauTransition[i], "%d %c %d", &etatSource, &symbole, &etatDest);

    // Trouver la colonne correspondant au symbole (a, b, c)
    int col = 0;
    if (symbole == 'a') col = 2;
    else if (symbole == 'b') col = 3;
    else if (symbole == 'c') col = 4;

    // Ajouter la transition dans la cellule correspondante
    char temp[10];
    sprintf(temp, "%d", etatDest);  // Convertir l'état destination en chaîne
    strcat(automate[etatSource][col], temp);  // Ajouter l'état destination dans la colonne appropriée
  }

  return automate;
}

void afficherAutomate(char*** automate, int nbEtats) {
  printf("\n=== Automate ===\n\n");

  // Affichage de l'en-tête
  for (int j = 0; j < 5; j++) {
    printf("%-10s", automate[0][j]);  // Alignement des colonnes
  }
  printf("\n-------------------------------------------------\n");

  // Affichage des lignes (états)
  for (int i = 1; i <= nbEtats; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%-10s", automate[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}