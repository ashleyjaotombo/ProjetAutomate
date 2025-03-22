#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"

void testerMot(Automate *automate, char *mot) {
    printf("Test de la fonction testerMot pour le mot : %s\n", mot);

    char *currentState = strdup(automate->entrees[0]);
    if (currentState == NULL) {
        perror("Erreur d'allocation mémoire");
        return;
    }

    int i = 0;
    while (mot[i] != '\0') {
        char symboleCourant = mot[i];
        int transitionTrouvee = 0;

        for (int j = 0; j < automate->nbTransitions; j++) {
            if (strcmp(automate->transitions[j].origine, currentState) == 0 &&
                automate->transitions[j].symbole == symboleCourant) {

                free(currentState);  // Libérer l'ancien état
                currentState = strdup(automate->transitions[j].destination);

                transitionTrouvee = 1;
                break;
                }
        }

        if (!transitionTrouvee) {
            printf("Mot non reconnu\n");
            free(currentState);
            return;
        }

        i++;
    }

    for (int j = 0; j < automate->tailleSorties; j++) {
        if (strcmp(currentState, automate->sorties[j]) == 0) {
            printf("Mot reconnu\n");
            free(currentState);
            return;
        }
    }

    printf("Mot non reconnu\n");
    free(currentState);
}
