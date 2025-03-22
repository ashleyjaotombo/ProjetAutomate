#ifndef AUTOMATE_H
#define AUTOMATE_H

#define MAX_TRANSITIONS 100
#define MAX_ETATS 100
#include <stdbool.h>
// Structure pour stocker une transition
typedef struct {
    /*int*/char *origine ;
    char symbole;
    /*int*/char *destination;
} Transition;

// Structure pour stocker l'automate
typedef struct {
    int nbEtats;
    int nbSymboles;
    int nbTransitions;
    /*int*/char **entrees;
    int tailleEntrees;
    /*int*/char **sorties;
    int tailleSorties;
    char * tableau_etats[MAX_ETATS];
    Transition transitions[MAX_TRANSITIONS];
} Automate;

typedef struct {
    char *etats[MAX_ETATS];  // Ensemble d'états
    int taille;            // Nombre d'états dans l'ensemble
} EtatAD;


// Fonction pour charger un automate depuis un fichier
Automate* chargerAutomate(const char *nomFichier);

// Fonction pour afficher un automate
void testAutomate(Automate *automate);

// Fonction pour libérer la mémoire de l'automate
void libererAutomate(Automate *automate);

void StandardiserAutomate(Automate *automate);

bool isDeterminiser(Automate *automate);

bool isComplet(Automate* automate);

Automate Determiniser(Automate *automate);

bool contientEtat(char *etat, EtatAD *etatAD);

void ajouterEtat(char *etat, EtatAD *etatAD);

void trierEtatAD(EtatAD *etatAD);

bool sontEgauxEtatsAD(EtatAD *a, EtatAD *b);

char* concatenerEtats(EtatAD *etatAD);

void creeEtatPoubelle(Automate* automate);

#endif
