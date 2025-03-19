#include <stdio.h>
#include <stdlib.h>
#include "Automate.h"

int main() {
    char nomFichier[25];
    printf("Quel automate voulez-vous utiliser ? ");
    scanf("%s", nomFichier);

    Automate *automate = chargerAutomate(nomFichier);

    testAutomate(automate);

    printf("\nVoulez-vous standardiser l'automate ? (1 = Oui, 2 = Non) : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        printf("Standardisation en cours...\n");
        StandardiserAutomate(automate);
        testAutomate(automate);

    }

    // Libération de la mémoire
    libererAutomate(automate);
    return 0;
}
