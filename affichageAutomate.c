#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"

char*** creationAutomate(Automate automate1) {
  // Allocation du tableau pour l'automate
  char ***automate = (char***)malloc((automate1.nbEtats + 1) * sizeof(char*));

  // Initialisation des lignes du tableau de l'automate
  for (int i = 0; i <= automate1.nbEtats; i++) {
    automate[i] = malloc((automate1.nbTransitions+2) * sizeof(char*)); // 5 colonnes
    for (int j = 0; j < automate1.nbTransitions+2 ; j++) {
      automate[i][j] = (char*)calloc(50, sizeof(char)); // Chaque cellule peut contenir une chaîne de 50 caractères
    }
  }

  // Compléter les titres des colonnes
  strcpy(automate[0][0], " ");
  strcpy(automate[0][1], "Etat");
  strcpy(automate[0][2], "a");
  for (int i = 3; i < automate1.nbSymboles+3; i++)
  {
    char temp[2];
    temp[0]=automate[0][i-1][0]+1;
    temp[1]='\0';
    strcpy(automate[0][i], temp);
  }


  //Compléter le nom des états
  automate[1][1]="0";
  for (int i=2; i<automate1.nbEtats+1; i++)
  {
    automate[i][1][0]=automate[i-1][1][0]+1;
  }

  //CORRRRECTTTTTT

  //Identification des états finaux et initiaux
  for (int i = 1; i <= automate1.nbEtats; i++) {
    for (int j = 0; j < automate1.tailleEntrees; j++) {

      // On utilise atoi pour convertir les chaines de caractères en entier
      if (atoi(automate[i][1]) == automate1.entrees[j]) {
        strcpy(automate[i][0], "E");
      }
    }
    for (int j = 0; j < automate1.tailleSorties; j++) {

      if (atoi(automate[i][1]) == automate1.sorties[j]) {
        strcat(automate[i][0], "S");
      }
    }
  }

  for (int i = 0; i < automate1.nbTransitions; i++) {
    for (int j = 1; j <= automate1.nbEtats; j++) { // On commence à 1 parce qu'on commence à remplir depuis la deuxième ligne
      if (automate1.transitions[i].origine == j - 1) { // On fait la correspondance entre les états d'origine de transition et nos états du tableau


        for (int k = 2; k < automate1.nbSymboles + 2; k++) { // On parcourt les symboles avec k. Le premier symbole est dans la colonne 2
          if (automate1.transitions[i].symbole == automate[0][k][0]) {

            char temp[10];
            temp[0]=automate1.transitions[i].destination+'0';

            // Ajouter la destination à la cellule correspondante
            if (strlen(automate[j][k]) == 0) {
              strcpy(automate[j][k], temp); // Si la case est vide, on ajoute directement la destination
            } else {
              strcat(automate[j][k], ","); // Sinon, on met d'abord une virgule
              strcat(automate[j][k], temp); // Ensuite on ajoute la destination à la cellule
            }
          }
        }
      }
    }
  }

  return automate;


}



void afficherAutomate(char*** automate, int nbEtats, int nbSymboles) {
  printf("\n=== Automate ===\n\n");
  for (int j = 0; j < nbSymboles + 2; j++) {
    printf("%-10s", automate[0][j]);
  }
  printf("\n-------------------------------------------------\n");

  for (int i = 1; i <= nbEtats; i++) {
    for (int j = 0; j < nbSymboles + 2; j++) {
      printf("%-10s", automate[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}