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




#endif //ECELECAR_HEADER_H
