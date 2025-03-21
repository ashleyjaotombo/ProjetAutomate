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
    automate->entrees = calloc(automate->tailleEntrees, sizeof(char*));

    for (int i = 0; i < automate->tailleEntrees; i++) {
        token = strtok(NULL, " ");
        if (token) {
            // Supprimer le caractère de nouvelle ligne \n s'il existe
            token[strcspn(token, "\n")] = 0;  // strcspn() trouve l'index de '\n' et le remplace par '\0'
            automate->entrees[i] = strdup(token);
        }
    }


    // États de sortie
    // États de sortie
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, " ");
    sscanf(token, "%d", &automate->tailleSorties);
    automate->sorties = calloc(automate->tailleSorties, sizeof(char*));

    for (int i = 0; i < automate->tailleSorties; i++) {
        token = strtok(NULL, " ");
        if (token) {
            // Supprimer le caractère de nouvelle ligne \n s'il existe
            token[strcspn(token, "\n")] = 0;  // strcspn() trouve l'index de '\n' et le remplace par '\0'
            automate->sorties[i] = strdup(token);
        }
    }


    // Nombre de transitions
    fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%d", &automate->nbTransitions);

    // Lecture des transitions
    for (int i = 0; i < automate->nbTransitions; i++) {
        fgets(ligne, sizeof(ligne), fichier);

        int origine, destination;
        char symbole;

        if (sscanf(ligne, "%d%c%d", &origine, &symbole, &destination) != 3) {
            printf("Erreur de lecture de la transition : %s\n", ligne);
            continue;
        }

        // Allocation et conversion en une seule ligne
        automate->transitions[i].origine = malloc(10);
        automate->transitions[i].destination = malloc(10);

        sprintf(automate->transitions[i].origine, "%d", origine);
        automate->transitions[i].symbole = symbole;
        sprintf(automate->transitions[i].destination, "%d", destination);
    }


    fclose(fichier);
    return automate;
}
void testAutomate(Automate *automate) {
    printf("\n--- Automate ---\n");
    printf("Nombre de symboles : %d\n", automate->nbSymboles);
    printf("Nombre d'etats : %d\n", automate->nbEtats);

    printf("Etats d'entree (%d) : ", automate->tailleEntrees);
    for (int i = 0; i < automate->tailleEntrees; i++)
        printf("%s ", automate->entrees[i]);
    printf("\n");

    printf("Etats de sortie (%d) : ", automate->tailleSorties);
    for (int i = 0; i < automate->tailleSorties; i++)
        printf("%s ", automate->sorties[i]);
    printf("\n");

    printf("Nombre de transitions : %d\n", automate->nbTransitions);
    for (int i = 0; i < automate->nbTransitions; i++) {
        printf("%s --%c--> %s\n", automate->transitions[i].origine, automate->transitions[i].symbole, automate->transitions[i].destination);
    }
}

void libererAutomate(Automate *automate) {
    for (int i = 0; i < automate->tailleEntrees; i++) {
        free(automate->entrees[i]);
    }
    free(automate->entrees);
    for (int i = 0; i < automate->tailleSorties; i++) {
        free(automate->sorties[i]);
    }
    free(automate->sorties);
    for (int i = 0; i < automate->nbTransitions; i++) {
        free(automate->transitions[i].origine);
        free(automate->transitions[i].destination);
    }
    free(automate);
}


void estStandard(Automate *automate) {
    if( automate->tailleEntrees==1) {
        printf("L'automate est standard");
        return;
    }
    printf("L'automate n'est pas standard");


}


void StandardiserAutomate(Automate *automate) {
    if( automate->tailleEntrees==1) {
        printf("L'automate est deja standardiser");
        return;
    }
    int nbrtransitioninitiale=automate->nbTransitions;
    int k=nbrtransitioninitiale-1;
    int existant=0;

        automate->nbEtats++;

        for (int i = 0; i < automate->tailleEntrees; i++)
            {
                for(int j = 0; j < automate->nbTransitions; j++)
                {
                    if(strcmp(automate->entrees[i],automate->transitions[j].origine )==0)
                    {
                        while (k < automate->nbTransitions && existant==0)
                        {

                            if((strcmp(automate->transitions[k].destination,automate->transitions[j].destination )==0 && automate->transitions[k].symbole ==automate->transitions[j].symbole)) {
                                existant=1;
                            }
                            k++;
                        }
                        if(existant==0) {
                            automate->transitions[automate->nbTransitions].destination=automate->transitions[j].destination;
                            automate->transitions[automate->nbTransitions].origine="I";
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
        automate->entrees[0]="1";
        automate->entrees[1]="I";
        automate->tableau_etats[automate->nbEtats-1]="I";


        }
