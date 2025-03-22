#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"
#include <stdbool.h>


Automate* Automate_minimiser(Automate *automate) {
    // Étape 1: Séparer les états finaux des non finaux
    for (int i = 0; i < Automate->nbEtats; i++) {
        partition[i] = Automate->etatsFinaux[i]; // 0 = non final, 1 = final
    }

    do {
        changement = 0;
        memset(nouveauPartition, -1, sizeof(nouveauPartition));

        int indexGroupe = 0;
        for (int i = 0; i < Automate->nbEtats; i++) {
            if (nouveauPartition[i] == -1) {
                nouveauPartition[i] = indexGroupe;
                for (int j = i + 1; j < Automate->nbEtats; j++) {
                    if (partition[i] == partition[j]) {
                        int identiques = 1;
                        for (int k = 0; k < Automate->nbSymboles; k++) {
                            int dest1 = -1, dest2 = -1;
                            for (int t = 0; t < Automate->nbTransitions; t++) {
                                if (Automate->transitions[t].origine == i && Automate->transitions[t].symbole == 'a' + k)
                                    dest1 = Automate->transitions[t].destination;
                                if (Automate->transitions[t].origine == j && Automate->transitions[t].symbole == 'a' + k)
                                    dest2 = Automate->transitions[t].destination;
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

        for (int i = 0; i < Automate->nbEtats; i++) {
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
    MinA.nbSymboles = Automate->nbSymboles;
    MinA.nbTransitions = 0;

    // Mapping des anciens états vers les nouveaux
    int mapping[MAX_ETATS];
    memset(mapping, -1, sizeof(mapping));
    
    for (int i = 0; i < Automate->nbEtats; i++) {
        if (mapping[partition[i]] == -1) {
            mapping[partition[i]] = MinA.nbEtats++;
        }
    }

    // Reconstruction des transitions
    for (int i = 0; i < Automate->nbTransitions; i++) {
        int origine = mapping[partition[Automate->transitions[i].origine]];
        int destination = mapping[partition[Automate->transitions[i].destination]];
        char symbole = Automate->transitions[i].symbole;
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
    return MinaA;
}
