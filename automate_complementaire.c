#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automate.h"

Automate* Automate_complementaire(Automate *automate) {
   if (automate == NULL) return NULL;

   // Créer un nouvel automate pour le complémentaire
   Automate *complementaire = malloc(sizeof(Automate));
   *complementaire = *automate; // Copier les métadonnées

   // Inverser les états de sortie
   int nouvelleTailleSorties = automate->nbEtats - automate->tailleSorties;
   complementaire->sorties = calloc(nouvelleTailleSorties, sizeof(char*));

   int k = 0;
   for (int i = 0; i < automate->nbEtats; i++) {
      int estSortie = 0;

      // Vérifier si l'état courant est dans les sorties de l'automate original
      for (int j = 0; j < automate->tailleSorties; j++) {
         if (strcmp(automate->tableau_etats[i], automate->sorties[j]) == 0) {
            estSortie = 1;
            break;
         }
      }

      // Si l'état n'est pas une sortie dans l'automate original, on l'ajoute
      if (estSortie==0) {
         complementaire->sorties[k] = strdup(automate->tableau_etats[i]);
         k++;
      }
   }

   complementaire->tailleSorties = nouvelleTailleSorties;

   return complementaire;
}