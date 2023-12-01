#include "header.h"

int main() {
    char* info_identifiant = "base";
    t_sommet sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(sommet);
    t_station info_station = tri_station(sommet);
    printf("TESTETES");
    afficher_station(info_station);
    trier_taches_selon_precedences(info_station.tache, info_station.nbr_taches_total);


    //Ce que j'ai ajouter

    // Appel de la fonction organiser_taches_dans_stations
    t_tache** taches_triees;
    int nbr_taches_triees;
    taches_triees = tri_topologique(info_station.tache, info_station.nbr_taches_total, &nbr_taches_triees);

    t_station stations[100]; // Vous devrez ajuster la taille en fonction de vos besoins
    int nbr_stations = 0;

    organiser_taches_dans_stations(taches_triees, nbr_taches_triees, stations, &nbr_stations, sommet);

    // Libérer la mémoire
    for (int i = 0; i < nbr_taches_triees; i++) {
        free(taches_triees[i]);
    }
    free(taches_triees);

//Fin de mon ajout dans le main

    liberer_memoire_sommet(sommet);
    liberer_memoire_station ( info_station);
    return 0;
}
