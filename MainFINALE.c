
#include <stdio.h>
#include <stdlib.h>
#include "Automate.h"

int main() {
    char nomFichier[25];
    char mot[100];  // Taille du mot à tester

    printf("Quel automate voulez-vous utiliser ? ");
    scanf("%s", nomFichier);

    Automate *automate = chargerAutomate(nomFichier);

  testAutomate(automate);

    char*** notreAutomate=creationAutomate(*automate);

     afficherAutomate(notreAutomate, automate->nbEtats, automate->nbSymboles);

    printf("\nVoulez-vous standardiser l'automate ? (1 = Oui, 2 = Non) : ");
    int choix;
    scanf("%d", &choix);


    if (choix == 1) {
        printf("Standardisation en cours...\n");
            StandardiserAutomate(automate);
        testAutomate(automate);

    }
    printf("Entrez un mot à tester : ");
    scanf("%s", mot);
    testerMot(automate, mot);
    notreAutomate=creationAutomate(*automate);
    afficherAutomate(notreAutomate, automate->nbEtats, automate->nbSymboles);

    // Libération de la mémoire

    Automate *complementaire = Automate_complementaire(automate);
    printf("\n--- Automate Complémentaire ---\n");
    testAutomate(complementaire);
    return 0;
}
