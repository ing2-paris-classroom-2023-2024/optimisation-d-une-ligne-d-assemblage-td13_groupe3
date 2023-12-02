
#ifndef ECELECAR_HEADER_H
#define ECELECAR_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    bool visite;
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


void organiser_taches_dans_stations(t_tache** taches_triees, int nbr_taches_triees, t_station* stations, int* nbr_stations, t_sommet info_sommet);
void tri_topologique_recursif(t_tache* tache, int* index, t_tache** resultat);
t_tache** tri_topologique(t_tache* taches, int nbr_taches, int* nbr_taches_triees);
void trier_taches_selon_precedences(t_tache* taches, int nbr_taches);


void repartir_taches_dans_stations(t_tache** taches_triees, int nbr_taches_triees, int temps_operation, int* nbr_stations);
bool peut_ajouter_tache(t_station* stations, int index_station, t_tache* tache);
bool verifier_exclusions_station(t_station* station, t_tache* tache);
bool verifier_precedences_station(t_station* station, t_tache* tache);
void initialiser_station(t_station* station, int temps_operation);
void ajouter_tache_a_station(t_station* station, t_tache* tache);
void afficher_taches_station(t_station station);
void liberer_memoire_station(t_station* station);


#endif //ECELECAR_HEADER_H
