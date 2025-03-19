#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichageAutomate.h"

int main(void) {
    //On demande à l'utilisateur de saisir le numéro du fichier
    FILE *fichier;
    char ligne[100];
    printf("Veuillez saisir le numéro du fichier test : ");
    char numFichier[25];
    scanf("%s", numFichier);

    //Lecture du fichier test
    fichier = fopen(numFichier, "r");
    if (fichier == NULL) {
        printf("Erreur dans l'ouverture du fichier test\n");
        return 0;
    }

    int nbEtats;
    int *entrees=calloc(nbEtats, sizeof(int));  //Pour stocker les états entrées
    int *sorties=calloc(nbEtats, sizeof(int));; //Pour stocker les sorties
    char **TableauTransition = calloc(20, sizeof(char *)); //On crée un tableau 2D qui regroupe les transitions
    int incrementTableauTransition = 0;
    int i = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = 0; //Pour ne pas lire le caractère saut de ligne

        if (i == 0) {  //On se trouve sur la première ligne
            sscanf(ligne, "%d", &nbEtats);
        }

        else if (i == 1) { //On est sur la 2ème ligne
            sscanf(ligne, "%d", &entrees[0]);
        }

        else if (i == 2) { //On est sur la 3ème ligne
            sscanf(ligne, "%d", &sorties[0]);
        }

        else { //On est sur les transitions
            TableauTransition[incrementTableauTransition] = strdup(ligne);
            incrementTableauTransition++;
        }
        i++;
    }
    fclose(fichier);

    // Affichage de la lecture du fichier
    printf("Nombre d'états: %d\n", nbEtats);
    printf("Etat initial: %d\n", entrees[0]);
    printf("Etat final: %d\n", sorties[0]);
    printf("Nombre de transitions: %d\n", incrementTableauTransition);
    for (int j = 0; j < incrementTableauTransition; j++) {
        printf("Transition : %s\n", TableauTransition[j]);
    }

    char*** automate1=creationAutomate(nbEtats, entrees, sorties, TableauTransition, incrementTableauTransition);
    afficherAutomate(automate1, nbEtats);


    return 0;
}