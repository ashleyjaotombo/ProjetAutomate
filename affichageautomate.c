
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"


char*** creationAutomate(Automate automate1) {
    // Allocation du tableau pour l'automate
    char ***automate = (char***)malloc((automate1.nbEtats + 1) * sizeof(char*));

    // Initialisation des lignes du tableau de l'automate
    for (int i = 0; i <= automate1.nbEtats; i++) {
        automate[i] = malloc((automate1.nbSymboles + 2) * sizeof(char*)); // +2 car on commence à la colonne 3
        for (int j = 0; j < automate1.nbSymboles + 2; j++) {
            automate[i][j] = (char*)calloc(50, sizeof(char));
        }
    }

    // Compléter les titres des colonnes
    strcpy(automate[0][0], " ");
    strcpy(automate[0][1], "Etat");
    strcpy(automate[0][2], "a");

    for (int i = 0; i < automate1.nbSymboles ; i++) {
        char temp[2];
        temp[0] = 'b' + i;
        temp[1] = '\0';
        strcpy(automate[0][i+3], temp);
    }

    // Compléter le nom des états

    for (int i = 0; i < automate1.nbEtats; i++) {
        strcpy(automate[i + 1][1], automate1.tableau_etats[i]);  // Conversion des états en chaîne
    }

    // Identification des états finaux et initiaux
    for (int i = 1; i <= automate1.nbEtats; i++) {
        for (int j = 0; j < automate1.tailleEntrees; j++) {
            if (strcmp(automate[i][1], automate1.entrees[j])==0) {
                strcpy(automate[i][0], "E");
            }
        }
        for (int j = 0; j < automate1.tailleSorties; j++) {
            if (strcmp(automate[i][1], automate1.sorties[j])==0) {
                strcat(automate[i][0], "S");
            }
        }
    }

    // On complète les transitions
    for (int i = 0; i < automate1.nbTransitions; i++) {
        for (int j = 1; j <= automate1.nbEtats; j++) {  // On commence à 1 parce qu'on commence à remplir depuis la deuxième ligne
            if (strcmp(automate1.transitions[i].origine, automate1.tableau_etats[j - 1])==0) {  // On fait la correspondance entre les états d'origine de transition et nos états du tableau

                for (int k = 2; k < automate1.nbSymboles + 2; k++) {  // On parcourt les symboles avec k. Le premier symbole est dans la colonne 2
                    if (automate1.transitions[i].symbole == automate[0][k][0]) {  // Vérifier si le symbole correspond

                        char temp[10];
                        sprintf(temp, "%d", automate1.transitions[i].destination);  // Convertir la destination en chaîne

                        // Ajouter la destination à la cellule correspondante
                        if (strlen(automate[j][k]) == 0) {
                            strcpy(automate[j][k], temp);  // Si la case est vide, on ajoute directement la destination
                        } else {
                            strcat(automate[j][k], ",");  // Sinon, on met d'abord une virgule
                            strcat(automate[j][k], temp);  // Ensuite on ajoute la destination à la cellule
                        }
                    }
                }
            }
        }
    }

    return automate;  // Retourner l'automate construit
}


void afficherAutomate(char*** automate, int nbEtats, int nbSymboles) {
    printf("\n=== Automate ===\n\n");
    for (int j = 0; j < nbSymboles + 2; j++) {  // Afficher les titres des colonnes
        printf("%-10s", automate[0][j]);
    }
    printf("\n-------------------------------------------------\n");

    for (int i = 1; i <= nbEtats; i++) {  // Afficher les lignes des états
        for (int j = 0; j < nbSymboles + 2; j++) {
            printf("%-10s", automate[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}