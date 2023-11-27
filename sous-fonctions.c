#include "header.h"

t_sommet recuperer_info_sommet(char* info_identifiant) {
    t_sommet info_sommet;
    char* chaine_temporaire = malloc (100* sizeof(char));

    // Chargement des données de précédence
    sprintf(chaine_temporaire, "../fichiers_ressources/01/precedences.txt");
    info_sommet.precedences = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_precedences), 0);

    // Chargement des données d'opération
    sprintf(chaine_temporaire, "../fichiers_ressources/01/operation.txt");
    info_sommet.operations = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_operations), 1);

    // Chargement des données d'exclusions
    sprintf(chaine_temporaire, "../fichiers_ressources/01/exclusions.txt");
    info_sommet.exclusions = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_exclusions), 1);


    // Chargement du temps de cycle
    sprintf(chaine_temporaire, "../fichiers_ressources/01/temps_cycle.txt");
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

t_station info_station_tache (t_sommet info_sommet){
    t_station info_station;

    info_station.nbr_taches_total = 0;
    printf("Nombre total d'operations : %d",info_sommet.nbr_total_operations );
    info_station.tache = (t_tache*) malloc (info_station.nbr_taches_total * sizeof(t_tache));
    for(int i = 0; i < info_sommet.nbr_total_operations; i++){
        info_station.tache = realloc(info_station.tache, (info_station.nbr_taches_total+1)*sizeof(t_tache) );
        info_station.tache[info_station.nbr_taches_total].identifiant = info_sommet.operations[i][0];
        info_station.tache[info_station.nbr_taches_total].poids = info_sommet.operations[i][1];
        info_station.tache[info_station.nbr_taches_total].nbr_total_taches_precedentes = 0;
        info_station.tache[info_station.nbr_taches_total].taches_precedentes = (t_tache**) malloc( info_station.tache[info_station.nbr_taches_total].nbr_total_taches_precedentes*sizeof(t_tache*));
        info_station.tache[info_station.nbr_taches_total].nbr_total_taches_exclusions = 0;
        info_station.tache[info_station.nbr_taches_total].taches_exclusions = (t_tache**) malloc( info_station.tache[info_station.nbr_taches_total].nbr_total_taches_exclusions*sizeof(t_tache*));
        printf("Station : %d -- total : %d\n", info_station.tache[info_station.nbr_taches_total].identifiant, info_station.nbr_taches_total);
        info_station.nbr_taches_total++;
    }
    return info_station;
}

void ajouter_exclusions(t_sommet info_sommet, t_station* info_station){

    for(int i = 0; i < info_sommet.nbr_total_exclusions; i++){
        t_tache* sommet_lu[2];

        for(int j = 0; j < info_station->nbr_taches_total; j++){
            if(info_sommet.exclusions[i][0] == info_station->tache[j].identifiant){
                sommet_lu[0] = &(info_station->tache[j]);
            }
        }
        for(int j = 0; j < info_station->nbr_taches_total; j++){
            if(info_sommet.exclusions[i][1] == info_station->tache[j].identifiant){
                sommet_lu[1] = &(info_station->tache[j]);
            }
        }

        sommet_lu[0]->taches_exclusions = realloc(sommet_lu[0]->taches_exclusions, (sommet_lu[0]-> nbr_total_taches_exclusions + 1) * sizeof(t_tache* ));
        sommet_lu[0]->taches_exclusions[sommet_lu[0]->nbr_total_taches_exclusions] = sommet_lu[1];
        sommet_lu[0]->nbr_total_taches_exclusions++;

        sommet_lu[1]->taches_exclusions= realloc(sommet_lu[1]->taches_exclusions, (sommet_lu[1]-> nbr_total_taches_exclusions + 1) * sizeof(t_tache* ));
        sommet_lu[1]->taches_exclusions[sommet_lu[1]->nbr_total_taches_exclusions] = sommet_lu[0];
        sommet_lu[1]->nbr_total_taches_exclusions++;

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

t_station tri_station(t_sommet info_sommet){
    t_station info_station = info_station_tache ( info_sommet);
    info_station.temps_operation = info_sommet.temps_operation;

    ajouter_exclusions( info_sommet, &info_station);
    ajouter_precedences( info_sommet, &info_station);

    return info_station;
}
void afficher_station (t_station info_station){
    printf("\nTache (Nombre de taches total : %d) :\n", info_station.nbr_taches_total);
    for(int i = 0; i < info_station.nbr_taches_total; i++){
        printf("Tache numero %d :\n", info_station.tache[i].identifiant);
        printf("Precedences (Nombre de precedences total : %d) : ", info_station.tache[i].nbr_total_taches_precedentes);
        for(int j = 0; j < info_station.tache[i].nbr_total_taches_precedentes; j++){
            printf("%d, ", info_station.tache[i].taches_precedentes[j]->identifiant);
        }
        printf("\n");
        printf("Exclusions (Nombre d'exclusions total : %d) : ", info_station.tache[i].nbr_total_taches_exclusions);
        for(int j = 0; j < info_station.tache[i].nbr_total_taches_exclusions; j++){
            printf("%d, ", info_station.tache[i].taches_exclusions[j]->identifiant);
        }
        printf("\n\n");
    }

}
void liberer_memoire_station (t_station info_station){
    for(int i = 0; i < info_station.nbr_taches_total; i++){
        free(info_station.tache[i].taches_precedentes);
        free(info_station.tache[i].taches_exclusions);

    }
}