#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"
#include <stdbool.h>


// Étape 1: Séparer les états finaux des non finaux
    for (int i = 0; i < A->nbEtats; i++) {
        partition[i] = A->etatsFinaux[i]; // 0 = non final, 1 = final
    }

    do {
        changement = 0;
        memset(nouveauPartition, -1, sizeof(nouveauPartition));

        int indexGroupe = 0;
        for (int i = 0; i < A->nbEtats; i++) {
            if (nouveauPartition[i] == -1) {
                nouveauPartition[i] = indexGroupe;
                for (int j = i + 1; j < A->nbEtats; j++) {
                    if (partition[i] == partition[j]) {
                        int identiques = 1;
                        for (int k = 0; k < A->nbSymboles; k++) {
                            int dest1 = -1, dest2 = -1;
                            for (int t = 0; t < A->nbTransitions; t++) {
                                if (A->transitions[t].origine == i && A->transitions[t].symbole == 'a' + k)
                                    dest1 = A->transitions[t].destination;
                                if (A->transitions[t].origine == j && A->transitions[t].symbole == 'a' + k)
                                    dest2 = A->transitions[t].destination;
                            }
                            if (dest1 != dest2 && partition[dest1] != partition[dest2]) {
                                identiques = 0;
                                break;
                            }
                        }
                        if (identiques) {
                            nouveauPartition[j] = indexGroupe;
                        }
                    }
                }
                indexGroupe++;
            }
        }

        for (int i = 0; i < A->nbEtats; i++) {
            if (partition[i] != nouveauPartition[i]) {
                changement = 1;
                break;
            }
        }
        memcpy(partition, nouveauPartition, sizeof(partition));

    } while (changement);

    // Création du nouvel automate minimisé
    Automate MinA;
    MinA.nbEtats = 0;
    MinA.nbSymboles = A->nbSymboles;
    MinA.nbTransitions = 0;

    // Mapping des anciens états vers les nouveaux
    int mapping[MAX_ETATS];
    memset(mapping, -1, sizeof(mapping));
    
    for (int i = 0; i < A->nbEtats; i++) {
        if (mapping[partition[i]] == -1) {
            mapping[partition[i]] = MinA.nbEtats++;
        }
    }

    // Reconstruction des transitions
    for (int i = 0; i < A->nbTransitions; i++) {
        int origine = mapping[partition[A->transitions[i].origine]];
        int destination = mapping[partition[A->transitions[i].destination]];
        char symbole = A->transitions[i].symbole;
        int existe = 0;

        for (int j = 0; j < MinA.nbTransitions; j++) {
            if (MinA.transitions[j].origine == origine &&
                MinA.transitions[j].destination == destination &&
                MinA.transitions[j].symbole == symbole) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            MinA.transitions[MinA.nbTransitions].origine = origine;
            MinA.transitions[MinA.nbTransitions].symbole = symbole;
            MinA.transitions[MinA.nbTransitions].destination = destination;
            MinA.nbTransitions++;
        }
    }

    // Remplacer l'automate d'origine par l'automate minimisé
    *A = MinA;
}
