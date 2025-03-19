#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"

#define MAX_LIGNE 100

Automate* chargerAutomate(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return NULL;
    }

    Automate *automate = malloc(sizeof(Automate));
    char ligne[MAX_LIGNE];

    // Lecture des données
    fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%d", &automate->nbSymboles);

    fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%d", &automate->nbEtats);

    // États d'entrée
    fgets(ligne, sizeof(ligne), fichier);
    char *token = strtok(ligne, " ");
    sscanf(token, "%d", &automate->tailleEntrees);
    automate->entrees = calloc(automate->tailleEntrees, sizeof(int));
    for (int i = 0; i < automate->tailleEntrees; i++) {
        token = strtok(NULL, " ");
        if (token) automate->entrees[i] = atoi(token);
    }

    // États de sortie
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, " ");
    sscanf(token, "%d", &automate->tailleSorties);
    automate->sorties = calloc(automate->tailleSorties, sizeof(int));
    for (int i = 0; i < automate->tailleSorties; i++) {
        token = strtok(NULL, " ");
        if (token) automate->sorties[i] = atoi(token);
    }

    // Nombre de transitions
    fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%d", &automate->nbTransitions);


    // Lecture des transitions
    for (int i = 0; i < automate->nbTransitions; i++) {
        fgets(ligne, sizeof(ligne), fichier);
        sscanf(ligne, "%d%c%d",
               &automate->transitions[i].origine,
               &automate->transitions[i].symbole,
               &automate->transitions[i].destination);
    }

    fclose(fichier);
    return automate;
}

void testAutomate(Automate *automate) {
    printf("\n--- Automate ---\n");
    printf("Nombre de symboles : %d\n", automate->nbSymboles);
    printf("Nombre d'états : %d\n", automate->nbEtats);

    printf("États d'entrée (%d) : ", automate->tailleEntrees);
    for (int i = 0; i < automate->tailleEntrees; i++)
        printf("%d ", automate->entrees[i]);
    printf("\n");

    printf("États de sortie (%d) : ", automate->tailleSorties);
    for (int i = 0; i < automate->tailleSorties; i++)
        printf("%d ", automate->sorties[i]);
    printf("\n");

    printf("Nombre de transitions : %d\n", automate->nbTransitions);
    for (int i = 0; i < automate->nbTransitions; i++) {
        printf("%d --%c--> %d\n",
               automate->transitions[i].origine,
               automate->transitions[i].symbole,
               automate->transitions[i].destination);
    }
}

void libererAutomate(Automate *automate) {
    free(automate->entrees);
    free(automate->sorties);
    free(automate);
}

void StandardiserAutomate(Automate *automate) {
    int nbrtransitioninitiale=automate->nbTransitions;
    int k=nbrtransitioninitiale-1;
    int existant=0;
    if( automate->tailleEntrees==1) {
        printf("L'automate est déjà standardiser");
        return;
    }
    else
        {
        automate->nbEtats++;

        for (int i = 0; i < automate->tailleEntrees; i++)
            {
                for(int j = 0; j < automate->nbTransitions; j++)
                {
                    if(automate->entrees[i]==automate->transitions[j].origine )
                    {
                        while (k < automate->nbTransitions && existant==0)
                            {

                            if((automate->transitions[k].destination!=automate->transitions[j].destination|| automate->transitions[k].symbole !=automate->transitions[j].symbole)) {
                                existant=1;
                            }
                            k++;
                        }
                        if(existant==0) {
                            automate->transitions[automate->nbTransitions].destination=automate->transitions[j].destination;
                            automate->transitions[automate->nbTransitions].origine=100;  //int choisi arbitrairement
                            automate->transitions[automate->nbTransitions].symbole=automate->transitions[j].symbole;
                            automate->nbTransitions++;
                        }
                        existant=0;
                        k=nbrtransitioninitiale-1;
                    }

                }
            }
        automate->tailleEntrees=1;
        automate->entrees = calloc(automate->tailleEntrees+1, sizeof(int));
        automate->entrees[0]=1;
        automate->entrees[1]=100;

        }
    }
