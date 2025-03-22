#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"

void testerMot(Automate *automate, char *mot) {
    printf("Test de la fonction testerMot pour le mot : %s\n", mot);
    char* currentState = malloc(sizeof(char)*10);
        automate->entrees[0];
    int i = 0;
    while (mot[i] != '\0') {
        char symboleCourant = mot[i];
        int transitionTrouvee = 0;
        for (int j = 0; j < automate->nbTransitions; j++) {
            if (strcmp(automate->transitions[j].origine, currentState)==0  &&
                automate->transitions[j].symbole == symboleCourant) {
                currentState = automate->transitions[j].destination;
                transitionTrouvee = 1;
                break;
                }
        }
        if (!transitionTrouvee) {
            printf("Mot non reconnu\n");
            return;
        }
        i++;
    }
    for (int j = 0; i < automate->tailleSorties; j++) {
        if (strcmp(currentState,automate->sorties[i])==0) {
            printf("Mot reconnu\n");
            return;
        }
    }
    printf("Mot non reconnu\n");
}