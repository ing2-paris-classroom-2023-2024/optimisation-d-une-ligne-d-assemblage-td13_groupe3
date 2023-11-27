#include "header.h"

int main() {
    char* info_identifiant = "base";
    t_sommet sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(sommet);
    t_station info_station = tri_station(sommet);
    printf("TESTETES");
    afficher_station(info_station);
    int* ordre = ordre_priorite(&sommet, &info_station);
    afficher_ordre(ordre, info_station.nbr_taches_total);

    free(ordre);
    liberer_memoire_sommet(sommet);
    liberer_memoire_station ( info_station);
    return 0;
}
