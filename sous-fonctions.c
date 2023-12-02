#include "header.h"

t_sommet recuperer_info_sommet(char* info_identifiant) {
    t_sommet info_sommet;
    char* chaine_temporaire = malloc (100* sizeof(char));

    // Chargement des données de précédence
    sprintf(chaine_temporaire, "../base/precedences.txt");
    info_sommet.precedences = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_precedences), 0);

    // Chargement des données d'opération
    sprintf(chaine_temporaire, "../base/operation.txt");
    info_sommet.operations = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_operations), 1);

    // Chargement des données d'exclusions
    sprintf(chaine_temporaire, "../base/exclusions.txt");
    info_sommet.exclusions = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_exclusions), 1);


    // Chargement du temps de cycle
    sprintf(chaine_temporaire, "../base/temps_cycle.txt");
    FILE* fichier = fopen(chaine_temporaire, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", chaine_temporaire);
        exit(EXIT_FAILURE);
    }

    if (!feof(fichier)) {
        fscanf(fichier, "%d", &(info_sommet.temps_operation));
        info_sommet.temps_operation *= 1000; // on multiplie par 1000 afin de ne pas avoir de float
    }

    fclose(fichier);
    return info_sommet;
}

int** remplir_sommet(char* nom_fichier, int* total, int condition_int_float){
    FILE* fichier = fopen(nom_fichier, "rw+");
    *total = 0;
    int** tableau = malloc(sizeof(int*) );

    while(!feof(fichier)){
        tableau = realloc(tableau, (*total + 1) * sizeof(int*) );
        tableau[*total] = malloc(2 * sizeof(int) );
        if(condition_int_float) {
            double temp = 0.001;
            fscanf(fichier, "%d %lf\n", &(tableau[*total][0]), &(temp));
            tableau[*total][1] = (int) (temp * 1000);
        }
        else{
            fscanf(fichier, "%d %d\n", &(tableau[*total][0]), &(tableau[*total][1]));
        }
        (*total)++;
    }
    fclose(fichier);
    printf("\n");
    return tableau;
}

void afficher_sommet (t_sommet info_sommet){

    printf("Precedences :\n");
    for(int i = 0; i < info_sommet.nbr_total_precedences; i++){
        printf("%d :\t%d\t%d\n", i, info_sommet.precedences[i][0], info_sommet.precedences[i][1]);
    }
    printf("\n");

    printf("Exclusions :\n");
    for(int i = 0; i < info_sommet.nbr_total_exclusions; i++){
        info_sommet.exclusions[i][1]=info_sommet.exclusions[i][1]/1000;
        printf("%d :\t%d\t%d\n", i, info_sommet.exclusions[i][0], info_sommet.exclusions[i][1]);
    }
    printf("\n");

    printf("Operations :\n");
    for(int i = 0; i < info_sommet.nbr_total_operations; i++){
        printf("%d :\t%d\t%d\n", i, info_sommet.operations[i][0],info_sommet.operations[i][1]);
    }
    printf("\nTemps operations : \n");
    printf("%d\n", info_sommet.temps_operation);
}


void liberer_memoire_sommet ( t_sommet info_sommet){
    for(int i = 0; i < info_sommet.nbr_total_precedences; i++){
        free(info_sommet.precedences[i]); // on libère la mémoire des colonnes de chaque ligne
    }
    free(info_sommet.precedences); // on libère la mémoire de chaque ligne

    for(int i = 0; i < info_sommet.nbr_total_exclusions; i++){
        free(info_sommet.exclusions[i]);
    }
    free(info_sommet.exclusions);
    for(int i = 0; i < info_sommet.nbr_total_operations; i++){
        free(info_sommet.operations[i]);
    }
    free(info_sommet.operations);
}
void ajouter_exclusions(t_sommet info_sommet, t_station* info_station) {
    for (int i = 0; i < info_sommet.nbr_total_exclusions; i++) {
        t_tache* tache_lue[2];

        for (int j = 0; j < info_station->nbr_taches_total; j++) {
            if (info_sommet.exclusions[i][0] == info_station->tache[j].identifiant) {
                tache_lue[0] = &(info_station->tache[j]);
            }
            if (info_sommet.exclusions[i][1] == info_station->tache[j].identifiant) {
                tache_lue[1] = &(info_station->tache[j]);
            }
        }

        tache_lue[0]->taches_exclusions = realloc(tache_lue[0]->taches_exclusions, (tache_lue[0]->nbr_total_taches_exclusions + 1) * sizeof(t_tache*));
        tache_lue[0]->taches_exclusions[tache_lue[0]->nbr_total_taches_exclusions] = tache_lue[1];
        tache_lue[0]->nbr_total_taches_exclusions++;

        tache_lue[1]->taches_exclusions = realloc(tache_lue[1]->taches_exclusions, (tache_lue[1]->nbr_total_taches_exclusions + 1) * sizeof(t_tache*));
        tache_lue[1]->taches_exclusions[tache_lue[1]->nbr_total_taches_exclusions] = tache_lue[0];
        tache_lue[1]->nbr_total_taches_exclusions++;
    }
}


void ajouter_precedences(t_sommet info_sommet, t_station* info_station){
    for(int i = 0; i < info_sommet.nbr_total_precedences; i++){

        t_tache * sommet_lu[2];
        for(int j = 0; j < info_station->nbr_taches_total; j++){
            if(info_sommet.precedences[i][0] == info_station->tache[j].identifiant){
                sommet_lu[0] = &(info_station->tache[j]);
            }
        }
        for(int j = 0; j < info_station->nbr_taches_total; j++){
            if(info_sommet.precedences[i][1] == info_station->tache[j].identifiant){
                sommet_lu[1] = &(info_station->tache[j]);
            }
        }

        sommet_lu[1]->taches_precedentes = realloc(sommet_lu[1]->taches_precedentes, (sommet_lu[1]->nbr_total_taches_precedentes + 1) * sizeof(t_tache*));

        sommet_lu[1]->taches_precedentes[sommet_lu[1]->nbr_total_taches_precedentes] = sommet_lu[0];
        sommet_lu[1]->nbr_total_taches_precedentes++;

    }
}
t_station info_station_tache(t_sommet info_sommet) {
    t_station info_station;

    info_station.nbr_taches_total = info_sommet.nbr_total_operations;
    info_station.tache = (t_tache*)malloc(info_station.nbr_taches_total * sizeof(t_tache));

    for (int i = 0; i < info_sommet.nbr_total_operations; i++) {
        info_station.tache[i].identifiant = info_sommet.operations[i][0];
        info_station.tache[i].poids = info_sommet.operations[i][1];
        info_station.tache[i].nbr_total_taches_precedentes = 0;
        info_station.tache[i].taches_precedentes = (t_tache*)malloc(info_station.tache[i].nbr_total_taches_precedentes * sizeof(t_tache));
        info_station.tache[i].nbr_total_taches_exclusions = 0;
        info_station.tache[i].taches_exclusions = (t_tache*)malloc(info_station.tache[i].nbr_total_taches_exclusions * sizeof(t_tache));

        // Ajouter les exclusions pour chaque tâche
        for (int j = 0; j < info_sommet.nbr_total_exclusions; j++) {
            if (info_sommet.exclusions[j][0] == info_station.tache[i].identifiant ||
                info_sommet.exclusions[j][1] == info_station.tache[i].identifiant) {
                info_station.tache[i].taches_exclusions = (t_tache*)realloc(info_station.tache[i].taches_exclusions, (info_station.tache[i].nbr_total_taches_exclusions + 1) * sizeof(t_tache));
                info_station.tache[i].taches_exclusions[info_station.tache[i].nbr_total_taches_exclusions] = &info_station.tache[j];
                info_station.tache[i].nbr_total_taches_exclusions++;
            }
        }
    }

    return info_station;
}
t_station tri_station(t_sommet info_sommet){
    t_station info_station = info_station_tache ( info_sommet);
    info_station.temps_operation = info_sommet.temps_operation;

    ajouter_exclusions( info_sommet, &info_station);
    ajouter_precedences( info_sommet, &info_station);

    return info_station;
}
// Fonction de tri topologique récursive
void tri_topologique_recursif(t_tache* tache, int* index, t_tache** resultat) {
    // Marquer la tâche comme visitée
    tache->visite = true;

    // Parcourir les tâches précédentes et trier récursivement
    for (int i = 0; i < tache->nbr_total_taches_precedentes; i++) {
        if (!(tache->taches_precedentes[i]->visite)) {
            tri_topologique_recursif(tache->taches_precedentes[i], index, resultat);
        }
    }

    // Ajouter la tâche au résultat
    resultat[*index] = tache;
    (*index)++;
}

// Fonction de tri topologique principale
t_tache** tri_topologique(t_tache* taches, int nbr_taches, int* nbr_taches_triees) {
    t_tache** resultat = malloc(nbr_taches * sizeof(t_tache*));
    *nbr_taches_triees = 0;

    // Initialiser les marques de visite
    for (int i = 0; i < nbr_taches; i++) {
        taches[i].visite = false;
    }

    // Parcourir toutes les tâches et déclencher le tri topologique si une tâche n'a pas été visitée
    for (int i = 0; i < nbr_taches; i++) {
        if (!taches[i].visite) {
            tri_topologique_recursif(&taches[i], nbr_taches_triees, resultat);
        }
    }

    return resultat;
}

// Fonction pour trier les tâches en fonction des précédences
void trier_taches_selon_precedences(t_tache* taches, int nbr_taches) {
    int nbr_taches_triees;
    t_tache** resultat = tri_topologique(taches, nbr_taches, &nbr_taches_triees);

    // Afficher ou utiliser les tâches triées selon les précédences (exemple d'affichage)
    printf("Taches triees en fonction des precedences :\n");
    for (int i = 0; i < nbr_taches_triees; i++) {
        printf("Tache numero %d\n", resultat[i]->identifiant);
    }

    // Libérer la mémoire
    free(resultat);
}

void repartir_taches_dans_stations(t_tache** taches_triees, int nbr_taches_triees, int temps_operation, int* nbr_stations) {
    // Initialisation des stations
    t_station* stations = NULL;
    int index_station = 0;

    for (int i = 0; i < nbr_taches_triees; i++) {
        t_tache* tache = taches_triees[i];

<<<<<<< Updated upstream
=======
<<<<<<< HEAD
        // Flag indiquant si la tâche a été ajoutée à une station existante
        bool ajout_station_existante = false;

        // Parcourir les stations existantes pour vérifier si la tâche peut être ajoutée à l'une d'elles
        for (int j = 0; j < *nbr_stations; ++j) {
            t_station* station = &stations[j];
            bool ajout_possible = true;
=======
>>>>>>> Stashed changes
        // Vérifier si la tâche peut être ajoutée à la station actuelle
        if (peut_ajouter_tache(stations, index_station, tache)) {
            // Ajouter la tâche à la station
            ajouter_tache_a_station(&stations[index_station], tache);
        } else {
            // Créer une nouvelle station et y ajouter la tâche
            stations = realloc(stations, (index_station + 1) * sizeof(t_station));
            initialiser_station(&stations[index_station], temps_operation);
            ajouter_tache_a_station(&stations[index_station], tache);
            index_station++;
        }
    }
<<<<<<< Updated upstream
=======
>>>>>>> df2bfbc011a08598b80a0b0e21397f14ffb83b13
>>>>>>> Stashed changes

    // Affichage des stations
    printf("\nStations :\n");
    for (int i = 0; i < index_station; i++) {
        printf("Station %d:\n", i + 1);
        afficher_taches_station(stations[i]);
    }

    // Mettre à jour le nombre total de stations
    *nbr_stations = index_station;

    // Libération de la mémoire
    for (int i = 0; i < index_station; i++) {
        liberer_memoire_station(&stations[i]);
    }
    free(stations);
}

// Fonction pour vérifier si une tâche peut être ajoutée à une station
bool peut_ajouter_tache(t_station* stations, int index_station, t_tache* tache) {
    for (int i = 0; i < index_station; i++) {
        // Vérifier les exclusions avec les tâches déjà présentes dans la station
        if (verifier_exclusions_station(&stations[i], tache)) {
            // Vérifier les précédences avec les tâches déjà présentes dans la station
            if (verifier_precedences_station(&stations[i], tache)) {
                return true;
<<<<<<< Updated upstream
            }
        }
    }
    return false;
}

// Fonction pour vérifier les exclusions avec les tâches déjà présentes dans une station
bool verifier_exclusions_station(t_station* station, t_tache* tache) {
    for (int i = 0; i < station->nbr_taches_total; i++) {
        // Allouer de la mémoire pour taches_exclusions si ce n'est pas déjà fait
        station->tache[i].taches_exclusions = (t_tache**)malloc(station->tache[i].nbr_total_taches_exclusions * sizeof(t_tache*));

        for (int j = 0; j < tache->nbr_total_taches_exclusions; j++) {
            if (station->tache[i].identifiant == tache->taches_exclusions[j]->identifiant) {
                return false; // La tâche est en exclusion avec une tâche déjà présente dans la station
            }
        }
    }
    return true; // Aucune exclusion détectée
}

// Fonction pour vérifier les précédences avec les tâches déjà présentes dans une station
bool verifier_precedences_station(t_station* station, t_tache* tache) {
    for (int i = 0; i < tache->nbr_total_taches_precedentes; i++) {
        bool precedente_trouvee = false;
        for (int j = 0; j < station->nbr_taches_total; j++) {
            if (station->tache[j].identifiant == tache->taches_precedentes[i]->identifiant) {
                precedente_trouvee = true;
                break;
            }
        }
        if (!precedente_trouvee) {
            return false; // Une précédence n'est pas satisfaite
        }
    }
    return true; // Toutes les précédences sont satisfaites
}

=======
            }
<<<<<<< HEAD

            // Vérifier si toutes les tâches précédentes sont dans la station actuelle ou dans des stations antérieures
            for (int k = 0; k < tache->nbr_total_taches_precedentes; ++k) {
                t_tache* tache_precedente = tache->taches_precedentes[k];
                bool precedente_presente = false;

                // Rechercher la tâche précédente dans la station actuelle
                for (int l = 0; l < station->nbr_taches_total; ++l) {
                    if (tache_precedente->identifiant == station->tache[l].identifiant) {
                        precedente_presente = true;
                        break;
                    }
                }

                // Si la tâche précédente n'est pas dans la station actuelle, vérifier les stations antérieures
                if (!precedente_presente) {
                    for (int l = 0; l < j; ++l) {
                        t_station* station_anterieure = &stations[l];
                        for (int m = 0; m < station_anterieure->nbr_taches_total; ++m) {
                            if (tache_precedente->identifiant == station_anterieure->tache[m].identifiant) {
                                precedente_presente = true;
                                break;
                            }
                        }
                    }
                }

                // Si une tâche précédente n'est pas présente, l'ajout n'est pas possible
                if (!precedente_presente) {
                    ajout_possible = false;
                    break;
                }
            }

            // Si toutes les conditions sont remplies, ajouter la tâche à la station existante
            if (ajout_possible) {
                t_tache* tache_station = &station->tache[station->nbr_taches_total];
                *tache_station = *tache;
                station->nbr_taches_total++;
                ajout_station_existante = true;
                break;
            }
        }

        // Si la tâche n'a pas été ajoutée à une station existante, créer une nouvelle station
        if (!ajout_station_existante) {
            t_station nouvelle_station = info_station_tache(info_sommet);
            t_tache* tache_station = &nouvelle_station.tache[nouvelle_station.nbr_taches_total];
            *tache_station = *tache;
            nouvelle_station.nbr_taches_total++;
            stations[*nbr_stations] = nouvelle_station;
            (*nbr_stations)++;
        }
    }

    // Afficher les stations et leurs tâches associées
    for (int i = 0; i < *nbr_stations; ++i) {
        printf("Station %d:\n", i + 1);
        for (int j = 0; j < stations[i].nbr_taches_total; ++j) {
            printf("Tache : %d\n", stations[i].tache[j].identifiant);
        }
        printf("\n");
=======
        }
    }
    return false;
}

// Fonction pour vérifier les exclusions avec les tâches déjà présentes dans une station
bool verifier_exclusions_station(t_station* station, t_tache* tache) {
    for (int i = 0; i < station->nbr_taches_total; i++) {
        // Allouer de la mémoire pour taches_exclusions si ce n'est pas déjà fait
        station->tache[i].taches_exclusions = (t_tache**)malloc(station->tache[i].nbr_total_taches_exclusions * sizeof(t_tache*));

        for (int j = 0; j < tache->nbr_total_taches_exclusions; j++) {
            if (station->tache[i].identifiant == tache->taches_exclusions[j]->identifiant) {
                return false; // La tâche est en exclusion avec une tâche déjà présente dans la station
            }
        }
    }
    return true; // Aucune exclusion détectée
}

// Fonction pour vérifier les précédences avec les tâches déjà présentes dans une station
bool verifier_precedences_station(t_station* station, t_tache* tache) {
    for (int i = 0; i < tache->nbr_total_taches_precedentes; i++) {
        bool precedente_trouvee = false;
        for (int j = 0; j < station->nbr_taches_total; j++) {
            if (station->tache[j].identifiant == tache->taches_precedentes[i]->identifiant) {
                precedente_trouvee = true;
                break;
            }
        }
        if (!precedente_trouvee) {
            return false; // Une précédence n'est pas satisfaite
        }
>>>>>>> df2bfbc011a08598b80a0b0e21397f14ffb83b13
    }
    return true; // Toutes les précédences sont satisfaites
}

>>>>>>> Stashed changes
// Fonction pour initialiser une station
void initialiser_station(t_station* station, int temps_operation) {
    station->temps_operation = temps_operation;
    station->nbr_taches_total = 0;
    station->tache = NULL;
}

// Fonction pour ajouter une tâche à une station
void ajouter_tache_a_station(t_station* station, t_tache* tache) {
    station->tache = realloc(station->tache, (station->nbr_taches_total + 1) * sizeof(t_tache));
    station->tache[station->nbr_taches_total] = *tache;
    station->nbr_taches_total++;
}

// Fonction pour afficher les tâches d'une station
void afficher_taches_station(t_station station) {
    for (int i = 0; i < station.nbr_taches_total; i++) {
        printf("Tache %d\n", station.tache[i].identifiant);
    }
    printf("\n");
}

// Fonction pour libérer la mémoire allouée à une station
void liberer_memoire_station(t_station* station) {
    free(station->tache);
}