#ifndef AUTOMATE_H
#define AUTOMATE_H

#define MAX_TRANSITIONS 100
#define MAX_ETATS 50

// Structure pour stocker une transition
typedef struct {
    int origine;
    char symbole;
    int destination;
} Transition;

// Structure pour stocker l'automate
typedef struct {
    int nbEtats;
    int nbSymboles;
    int nbTransitions;
    int *entrees;
    int tailleEntrees;
    int *sorties;
    int tailleSorties;
    int tableau_etats[MAX_ETATS];
    Transition transitions[MAX_TRANSITIONS];
} Automate;

// Fonction pour charger un automate depuis un fichier
Automate* chargerAutomate(const char *nomFichier);

// Fonction pour afficher un automate
void testAutomate(Automate *automate);

// Fonction pour libérer la mémoire de l'automate
void libererAutomate(Automate *automate);

void StandardiserAutomate(Automate *automate);

void estStandard(Automate *automate);

void afficherAutomate(char*** automate, int nbEtats, int nbSymboles);

char*** creationAutomate(Automate automate1);

#endif
