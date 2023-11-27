
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
    struct tache** taches_exclusions;
    struct tache** taches_precedentes;
    int nbr_total_taches_exclusions;
    int nbr_total_taches_precedentes;

}t_tache;


t_sommet recuperer_info_sommet(char* info_identifiant);
int** remplir_sommet();
void afficher_sommet (t_sommet info_sommet);
void liberer_memoire_sommet ( t_sommet info_sommet);


t_station tri_station(t_sommet info_sommet);
void afficher_station (t_station info_station);
void liberer_memoire_station (t_station info_station);

int* ordre_priorite(t_sommet* info_sommet, t_station* info_station);
void dfs(t_station* info_station, int tache_actuelle, int* visite, int* ordre, int* index_ordre);
void afficher_ordre(int* ordre, int taille);
t_tache* tache_prioritaire(t_sommet* sommet,t_station* info_station);

#endif //ECELECAR_HEADER_H
