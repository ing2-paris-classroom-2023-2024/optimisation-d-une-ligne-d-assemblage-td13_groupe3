#include "header.h"

int main() {
    char* info_identifiant = "base";
    t_sommet info_sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(info_sommet);
    t_station info_station = tri_station(info_sommet);
    afficher_station(info_station);
    trier_taches_selon_precedences(info_station.tache, info_station.nbr_taches_total);


    t_graph graphe;
    initialisationGraphe(&graphe, info_sommet.nbr_total_operations);

    // Ajouter les arêtes d'exclusion au graphe
    for (int i = 0; i < info_sommet.nbr_total_exclusions; i++) {
        ajouterArrete(&graphe, info_sommet.exclusions[i][0], info_sommet.exclusions[i][1]);
    }

    // Ajouter les arêtes de précédence au graphe
    for (int i = 0; i < info_sommet.nbr_total_precedences; i++) {
        ajouterArrete(&graphe, info_sommet.precedences[i][0], info_sommet.precedences[i][1]);
    }

    int couleurs[MAX_OPERATIONS + 1];
    colorerGraphe(&graphe, couleurs);
    afficherStations(&graphe, couleurs);
    int* nbr_stations;
    verifierEtAjouterNouvelleStation(info_sommet, &info_station, nbr_stations);

    // Libérer la mémoire
    liberer_memoire_sommet(info_sommet);
    free(info_station.tache);

    return 0;
    /*
    char* info_identifiant = "base";
    t_sommet sommet = recuperer_info_sommet(info_identifiant);
    afficher_sommet(sommet);
    t_station info_station = tri_station(sommet);
    //afficher_station(info_station);
    trier_taches_selon_precedences(info_station.tache, info_station.nbr_taches_total);

*/
    //Ce que j'ai ajouter
/*
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
*/



/*
    // Créer un tableau de tâches à partir des informations du sommet
    t_tache* taches = malloc(sommet.nbr_total_precedences * sizeof(t_tache));
    for (int i = 0; i < sommet.nbr_total_precedences; i++) {
        taches[i].identifiant = sommet.precedences[i][0];
        taches[i].poids = 0; // Vous devez définir le poids selon vos besoins
        taches[i].visite = false;
        // Copier les exclusions depuis sommet.exclusions[i]
        taches[i].taches_exclusions = malloc(sommet.nbr_total_exclusions * sizeof(t_tache*));
        for (int j = 0; j < sommet.nbr_total_exclusions; j++) {
            // Vous devez trouver la tâche correspondante dans le tableau taches
            // et l'assigner à taches[i].taches_exclusions[j]
        }
        taches[i].nbr_total_taches_exclusions = sommet.nbr_total_exclusions;
        // Copier les précédences depuis sommet.precedences[i]
        taches[i].taches_precedentes = malloc(sommet.nbr_total_precedences * sizeof(t_tache*));
        for (int j = 0; j < sommet.nbr_total_precedences; j++) {
            // Vous devez trouver la tâche correspondante dans le tableau taches
            // et l'assigner à taches[i].taches_precedentes[j]
        }
        taches[i].nbr_total_taches_precedentes = sommet.nbr_total_precedences;
    }

    // Trier les tâches selon les précédences
    //trier_taches_selon_precedences(taches, sommet.nbr_total_precedences);

    // Répartir les tâches dans les stations
    int nbr_stations;
    repartir_taches_dans_stations(&taches, sommet.nbr_total_precedences, sommet.temps_operation, &nbr_stations);

    // Libérer la mémoire allouée
    for (int i = 0; i < sommet.nbr_total_precedences; i++) {
        free(taches[i].taches_exclusions);
        free(taches[i].taches_precedentes);
    }
    free(taches);
//Fin de mon ajout dans le main

    liberer_memoire_sommet(sommet);

    return 0;*/
}
