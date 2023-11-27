#include "header.h"

int main() {
    char* info_identifiant = "01";
    t_sommet sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(sommet);
    return 0;
}
