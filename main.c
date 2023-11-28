#include "header.h"

int main() {
    char* info_identifiant = "base";
    t_sommet sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(sommet);
    t_station info_station = tri_station(sommet);
    printf("TESTETES");
    afficher_station(info_station);
    trier_taches_selon_precedences(info_station.tache, info_station.nbr_taches_total);
    liberer_memoire_sommet(sommet);
    liberer_memoire_station ( info_station);
    return 0;
}
