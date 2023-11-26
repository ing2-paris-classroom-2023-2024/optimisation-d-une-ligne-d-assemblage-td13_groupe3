//
// Created by alang on 22/11/2023.
//

#ifndef ECELECAR_HEADER_H
#define ECELECAR_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sommet {

    int temps_operation;
    int** exclusions; //  pointeur vers un pointeur
    int** precedences; // utilisé pour stocker l'adresse d'un tableau de pointeurs d'entiers
    int** operations;
    int nbr_total_exclusions;
    int nbr_total_precedences;
    int nbr_total_operations;

}t_sommet;

typedef struct station{

    int temps_operation;
    int nbr_taches_total;
    struct tache* tache;

}t_station;

typedef struct tache{

    int identifiant;
    int poids;
    struct tache** taches_suivantes;
    struct tache** taches_precedentes;
    int nbr_total_taches_suivantes;
    int nbr_total_taches_precedentes;

}t_tache;



int** remplir_sommet();
void afficher_sommet (t_sommet info_sommet);
void liberer_memoire ( t_sommet info_sommet);





// Espace des Bibliothèques :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// **********  MACROS   **********




// ********** STRUCTURE **********


typedef struct DATAS {
    int TCYCLE;         // Temps de Cycle
    int** EXCLUSIONS;    // Données d'exclusion
    int EXCLUSIONS_TOT;  // Nombre total d'exclusion
    int** PRECEDENCES;   // Données de précédence
    int PRECEDENCES_TOT; // Nombre total de precedence
    int** OPERATIONS ;   // Données d'opération
    int OPERATIONS_TOT;  // Nombre total d'operation
} DATAS;


typedef struct DATASET {
    int T_CYCLE;
    int TASK_TOT;
    struct TASK* TASKS;
} DATASET;
typedef struct TASK;
typedef struct TASK {
    int BASEID;
    int POIDS;
    struct TASK** P;
    int P_TOT;
    struct TASK** E;
    int E_TOT;
} TASK;




// **********  PROTOS   **********

// Protos de Chargement de Données
DATAS SCANDATAS(char* jeu_donnees);
int** FILLDATAS(char* fname, int* tot, int cond);
void DISPDATAS(DATAS datas);
void FREEDATAS(DATAS datas);

// Protos de l'Ordonnancement des Données
DATASET DATASORT(DATAS datas);
void DISPDATASET(DATASET dataset);
void FREEDATASET(DATASET dataset);

// Algorithme
void ALGO(DATASET dataset);
#endif //ECELECAR_HEADER_H
