#include <stdio.h>
#include <stdlib.h>
#include "Automate.h"
#include "Determinisation.h"

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

    printf("\nVoulez-vous voir si l'automate est determiniser? (1 = Oui, 2 = Non) : ");
    scanf("%d", &choix);
    if(choix == 1) {
        bool isDeter = false;
        printf("Determiniser en cours...\n");
        isDeter=isDeterminiser(automate);
        printf("%s",isDeter? "Determiniser":"pas determiniser");
        testAutomate(automate);

    }
    printf("Voulez-vous voir si l'automate est complet ? (1 = Oui, 2 = Non) :  ");
    scanf("%d", &choix);
    if(choix == 1) {
        bool isComp = false;
        printf("Traitement en cours...\n");
        isComp = isComplet(automate);
        printf("%s",isComp? "Complet":"pas complet");
        testAutomate(automate);
    }

    printf("voulez-vous determiniser l'automate ? (1 = Oui, 2 = Non) : ");
    scanf("%d", &choix);
    if(choix == 1) {
        Automate AD = Determiniser(automate);
        for(int i=0; i<AD.tailleEntrees;i++) {
            printf("la valeur est %s",*AD.entrees);

        }
        testAutomate(&AD);

    }

    // Libération de la mémoire
    libererAutomate(automate);
    return 0;
}
