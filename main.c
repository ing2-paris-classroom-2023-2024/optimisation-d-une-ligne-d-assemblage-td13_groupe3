#include "header.h"

int main() {
    char* info_identifiant = "01";
    t_sommet sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(sommet);
    setbuf(stdout, 0);
    char* jeu_donnees = "01";
    DATAS datas = SCANDATAS(jeu_donnees);
    DISPDATAS(datas);
    DATASET dataset = DATASORT(datas);
    DISPDATASET(dataset);

    ALGO(dataset);

    FREEDATASET(dataset);
    return 0;
}
