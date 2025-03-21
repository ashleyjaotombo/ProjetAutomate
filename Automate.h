#ifndef AUTOMATE_H
#define AUTOMATE_H

#define MAX_TRANSITIONS 100
#define MAX_ETATS 50

// Structure pour stocker une transition
typedef struct {
    char* origine;
    char symbole;
    char* destination;
} Transition;

// Structure pour stocker l'automate
typedef struct {
    int nbEtats;
    int nbSymboles;
    int nbTransitions;
    char**entrees;
    int tailleEntrees;
    char**sorties;
    int tailleSorties;
    char * tableau_etats[MAX_ETATS];
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
