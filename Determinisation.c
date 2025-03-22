//
// Created by yanic on 19/03/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"
#include "Determinisation.h"
#include <stdbool.h>

// Fonction pour verifier si un etat est dans un ensemble
bool contientEtat(char *etat, EtatAD *etatAD) {
    for (int i = 0; i < etatAD->taille; i++) {
        if (strcmp(etatAD->etats[i], etat) == 0) {
            return true;
        }
    }
    return false;
}

// Fonction pour ajouter un etat à un ensemble
void ajouterEtat(char *etat, EtatAD *etatAD) {
    if (!contientEtat(etat, etatAD)) {
        etatAD->etats[etatAD->taille] = strdup(etat); // Copie la chaîne
        etatAD->taille++;
    }
}

// Fonction pour trier les etats d'un ensemble
void trierEtatAD(EtatAD *etatAD) {
    for (int i = 0; i < etatAD->taille - 1; i++) {
        for (int j = i + 1; j < etatAD->taille; j++) {
            if (strcmp(etatAD->etats[i], etatAD->etats[j]) > 0) {
                char *temp = etatAD->etats[i];
                etatAD->etats[i] = etatAD->etats[j];
                etatAD->etats[j] = temp;
            }
        }
    }
}

// Fonction pour comparer deux ensembles d'etats
bool sontEgauxEtatsAD(EtatAD *a, EtatAD *b) {
    if (a->taille != b->taille) return false;
    for (int i = 0; i < a->taille; i++) {
        if (strcmp(a->etats[i], b->etats[i]) != 0) {
            return false;
        }
    }
    return true;
}

// Fonction pour verifier si un automate est dejà deterministe
bool isDeterminiser(Automate* automate) {
    // Verifier s'il y a un seul etat initial
    if (automate->tailleEntrees > 1) {
        return false;  // Plus d'un etat initial : automate non deterministe
    }

    // Verifier que les transitions sont uniques pour chaque symbole
    for (int i = 0; i < automate->nbEtats; i++) {  // Parcourir tous les etats
        char symbolesDejaVus[automate->nbTransitions];
        int nbSymbolesDejaVus = 0;

        for (int k = 0; k < automate->nbTransitions; k++) {  // Parcourir toutes les transitions
            // Convertir l'origine de la transition en entier pour la comparaison
            int origineTransition = atoi(automate->transitions[k].origine);

            // Verifier si la transition part de l'etat i
            if (origineTransition == i) {
                char symboleCourant = automate->transitions[k].symbole;

                // Verifier si ce symbole a dejà ete vu pour cet etat
                bool symboleDejaVu = false;
                for (int s = 0; s < nbSymbolesDejaVus; s++) {
                    if (symbolesDejaVus[s] == symboleCourant) {
                        symboleDejaVu = true;
                        break;
                    }
                }

                // Si le symbole a dejà ete vu, l'automate n'est pas deterministe
                if (symboleDejaVu) {
                    return false;
                }

                // Ajouter le symbole à la liste des symboles dejà vus
                symbolesDejaVus[nbSymbolesDejaVus] = symboleCourant;
                nbSymbolesDejaVus++;
            }
        }
    }

    // Si toutes les conditions sont valides, retourne true
    return true;
}

bool isComplet(Automate* automate) {
    // Verifier si le nombre de transitions correspond à nbEtats * nbSymboles
    if (automate->nbTransitions != automate->nbEtats * automate->nbSymboles) {
        return false;  // L'automate est incomplet
    }

    // Parcourir tous les etats
    for (int i = 0; i < automate->nbEtats; i++) {
        // Tableau pour stocker les symboles deja vus pour cet etat
        char symbolesDejaVus[automate->nbSymboles];
        int nbSymbolesTrouves = 0;  // Nombre de symboles dejà vus pour cet etat

        // Parcourir toutes les transitions pour cet etat
        for (int k = 0; k < automate->nbTransitions; k++) {
            // Convertir l'origine de la transition en entier
            int origineTransition = atoi(automate->transitions[k].origine);

            // Verifier si la transition part de l'etat i
            if (origineTransition == i) {
                char symboleCourant = automate->transitions[k].symbole;

                // Verifier si ce symbole a dejà ete vu pour cet etat
                bool symboleDejaVu = false;
                for (int l = 0; l < nbSymbolesTrouves; l++) {
                    if (symbolesDejaVus[l] == symboleCourant) {
                        symboleDejaVu = true;
                        break;  // Le symbole a deja ete vu
                    }
                }

                // Si le symbole a deja ete vu, l'automate n'est pas complet
                if (symboleDejaVu) {
                    return false;
                }

                // Ajouter le symbole à la liste des symboles deja vus
                symbolesDejaVus[nbSymbolesTrouves] = symboleCourant;
                nbSymbolesTrouves++;
            }
        }

        // Verifier si tous les symboles ont ete trouves pour cet etat
        if (nbSymbolesTrouves != automate->nbSymboles) {
            return false;  // Un symbole est manquant, l'automate est incomplet
        }
    }

    // Si toutes les combinaisons (etat, symbole) ont une transition, l'automate est complet
    return true;
}


// Fonction pour concatener les etats d'un ensemble en une chaine de caracteres
char* concatenerEtats(EtatAD *etatAD) {
    // Calculer la taille totale necessaire
    int tailleTotale = 1; // +1 pour le '\0'
    for (int i = 0; i < etatAD->taille; i++) {
        tailleTotale += strlen(etatAD->etats[i]);
    }

    // Allouer la memoire pour la chaîne resultante
    char *resultat = malloc(tailleTotale);
    // Concatenation des etats
    resultat[0] = '\0';
    for (int i = 0; i < etatAD->taille; i++) {
        strcat(resultat, etatAD->etats[i]);
    }

    return resultat;
}
//Fonction pour cree l'etat poubelle
void creeEtatPoubelle(Automate* automate) {
    ajouterEtat("P", automate);
}


// Fonction pour determiniser l'automate
Automate Determiniser(Automate *automate) {
    if (isDeterminiser(automate)&&isComplet(automate)) {
        printf("L'automate est deja deterministe et complet.\n");
        return *automate;
    }

    Automate afd = {0};

    // Initialisation de l'etat initial AFD
    EtatAD etatInitialAD = { .taille = 0 };
    for (int i = 0; i < automate->tailleEntrees; i++) {
        ajouterEtat(automate->entrees[i], &etatInitialAD);
    }
    trierEtatAD(&etatInitialAD);

    // Concatenation des etats initiaux
    char *etatInitialStr = concatenerEtats(&etatInitialAD);
    // Stocker l'etat initial dans l'AFD
    afd.entrees = malloc(sizeof(char *));
    afd.entrees[0] = etatInitialStr;
    afd.tailleEntrees = 1;
    afd.nbEtats++;

    // Tableau pour stocker les etats de l'AFD
    EtatAD etatsAD[MAX_ETATS];
    etatsAD[0] = etatInitialAD;
    int nbEtatsAD = 1;

    // Ajouter l'etat poubelle "P" à l'AFD
    EtatAD etatPoubelleAD = { .taille = 0 };
    ajouterEtat("P", &etatPoubelleAD);
    etatsAD[nbEtatsAD] = etatPoubelleAD;
    nbEtatsAD++;
    afd.nbEtats++;

    // Boucle principale de determinisation
    for (int i = 0; i < nbEtatsAD; i++) {
        EtatAD etatCourant = etatsAD[i];

        // Traiter tous les symboles possibles
        for (int s = 0; s < automate->nbTransitions; s++) {
            char symbole = automate->transitions[s].symbole;

            // Calculer l'ensemble atteignable
            EtatAD nouvelEtatAD = { .taille = 0 };
            for (int e = 0; e < etatCourant.taille; e++) {
                char *etatAFN = etatCourant.etats[e];
                for (int t = 0; t < automate->nbTransitions; t++) {
                    if (strcmp(automate->transitions[t].origine, etatAFN) == 0 &&
                        automate->transitions[t].symbole == symbole) {
                        ajouterEtat(automate->transitions[t].destination, &nouvelEtatAD);
                    }
                }
            }

            if (nouvelEtatAD.taille == 0) {
                nouvelEtatAD = etatPoubelleAD;
            }
            /*if (nouvelEtatAD.taille == 0) continue; // Aucun etat atteint*/

            trierEtatAD(&nouvelEtatAD);

            // Verifier si cet ensemble d'etats existe dejà
            bool existeDeja = false;
            int indexEtatAD = -1;
            for (int j = 0; j < nbEtatsAD; j++) {
                if (sontEgauxEtatsAD(&etatsAD[j], &nouvelEtatAD)) {
                    existeDeja = true;
                    indexEtatAD = j;
                    break;
                }
            }

            // Si c'est un nouvel ensemble, l'ajouter à l'AFD
            if (!existeDeja) {
                etatsAD[nbEtatsAD] = nouvelEtatAD;
                indexEtatAD = nbEtatsAD;
                nbEtatsAD++;
                afd.nbEtats++;
            }

            // Ajouter la transition
            Transition nouvelleTransition;
            nouvelleTransition.origine = concatenerEtats(&etatCourant);
            nouvelleTransition.symbole = symbole;
            nouvelleTransition.destination = concatenerEtats(&etatsAD[indexEtatAD]);

            // Verifier si la transition existe dejà
            bool transitionExiste = false;
            for (int k = 0; k < afd.nbTransitions; k++) {
                if (strcmp(nouvelleTransition.origine, afd.transitions[k].origine) == 0 &&
                    nouvelleTransition.symbole == afd.transitions[k].symbole &&
                    strcmp(nouvelleTransition.destination, afd.transitions[k].destination) == 0) {
                    transitionExiste = true;
                    break;
                    }
            }
            // Si la transition n'existe pas, l'ajouter à l'automate
            if (!transitionExiste) {
                afd.transitions[afd.nbTransitions] = nouvelleTransition;
                afd.nbTransitions++;
            }
        }
    }

    // Definir les etats de sortie de l'AFD
    afd.sorties = malloc(nbEtatsAD * sizeof(char *));
    afd.tailleSorties = 0;

    for (int i = 0; i < nbEtatsAD; i++) {
        bool estFinal = false;
        for (int j = 0; j < etatsAD[i].taille; j++) {
            char *etat = etatsAD[i].etats[j];
            for (int k = 0; k < automate->tailleSorties; k++) {
                if (strcmp(etat, automate->sorties[k]) == 0) {
                    estFinal = true;
                    break;
                }
            }
            if (estFinal) break;
        }

        // Verifie s'il est dejà ajoute
        if (estFinal) {
            bool dejaAjoute = false;
            for (int x = 0; x < afd.tailleSorties; x++) {
                if (strcmp(afd.sorties[x], concatenerEtats(&etatsAD[i])) == 0) {
                    dejaAjoute = true;
                    break;
                }
            }
            if (!dejaAjoute) {
                afd.sorties[afd.tailleSorties] = concatenerEtats(&etatsAD[i]);
                afd.tailleSorties++;
            }
        }
    }
    afd.nbSymboles=automate->nbSymboles;



    return afd;
}

