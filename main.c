
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichageAutomate.h"


#define MAX_TRANSITIONS 50  // Taille max pour les transitions
#define MAX_LIGNE 100       // Taille max d'une ligne

int main() {
    FILE *fichier;
    char ligne[MAX_LIGNE];
    printf("quel automate voulez-vous utiliser :  ");
    char numFichier[25];
    scanf("%s", numFichier);

    //Lecture du fichier test
    fichier = fopen(numFichier, "r");
    if (fichier == NULL) {
        printf("Erreur dans l'ouverture du fichier test\n");
        return 0;
    }

    int nbEtats, nbsymbole, nbTransitions;
    int *entrees, *sorties;
    int taille1, taille2;
    char **TableauTransition = calloc(MAX_TRANSITIONS, sizeof(char *)); // Tableau pour stocker les transitions
    int incrementTableauTransition = 0;

    int i = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Supprimer le saut de ligne
        ligne[strcspn(ligne, "\n")] = 0;

        if (i == 0) { // Nombre de symboles
            sscanf(ligne, "%d", &nbsymbole);
        }
        else if (i == 1) { // Nombre d'états
            sscanf(ligne, "%d", &nbEtats);
        }
        else if (i == 2) { // États d'entrée
            char *token = strtok(ligne, " ");
            sscanf(token, "%d", &taille1); // Nombre d'états d'entrée
            entrees = calloc(taille1, sizeof(int));

            for (int j = 0; j < taille1; j++) {
                token = strtok(NULL, " ");
                if (token) {
                    entrees[j] = atoi(token);
                }
            }
        }
        else if (i == 3) { // États de sortie
            char *token = strtok(ligne, " ");
            sscanf(token, "%d", &taille2); // Nombre d'états de sortie
            sorties = calloc(taille2, sizeof(int));

            for (int j = 0; j < taille2; j++) {
                token = strtok(NULL, " ");
                if (token) {
                    sorties[j] = atoi(token);
                }
            }
        }
        else if (i == 4) { // Nombre de transitions
            sscanf(ligne, "%d", &nbTransitions);
        }
        else { // Transitions
            if (incrementTableauTransition < MAX_TRANSITIONS) {
                TableauTransition[incrementTableauTransition] = strdup(ligne);
                incrementTableauTransition++;
            }
        }

        i++;
    }

    fclose(fichier);

    // Affichage des données pour vérifier
    printf("Nombre de symboles : %d\n", nbsymbole);
    printf("Nombre d'états : %d\n", nbEtats);

    printf("États d'entrée (%d) : ", taille1);
    for (int j = 0; j < taille1; j++) printf("%d ", entrees[j]);
    printf("\n");

    printf("États de sortie (%d) : ", taille2);
    for (int j = 0; j < taille2; j++) printf("%d ", sorties[j]);
    printf("\n");

    printf("Nombre de transitions : %d\n", nbTransitions);
    for (int j = 0; j < incrementTableauTransition; j++) {
        printf("Transition %d : %s\n", j + 1, TableauTransition[j]);
        free(TableauTransition[j]); // Libérer la mémoire de chaque transition
    }

    char*** automate1=creationAutomate(nbEtats, entrees, sorties, TableauTransition, incrementTableauTransition);
    afficherAutomate(automate1, nbEtats);

    free(entrees);
    free(sorties);
    free(TableauTransition); // Libérer le tableau

    return 0;
}

