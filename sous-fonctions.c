#include "header.h"

t_sommet recuperer_info_sommet(char* info_identifiant) {
    t_sommet info_sommet;
    char* chaine_temporaire = malloc (100* sizeof(char));

    // Chargement des données de précédence
    sprintf(chaine_temporaire, "../fichiers_ressources/01/precedences.txt");
    printf("%s", chaine_temporaire);
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
/*
int** remplir_sommet(char* nom_fichier, int* total, int condition) {
    FILE* fichier = fopen(nom_fichier, "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }



    *total = 0;
    int** tableau = malloc(100* sizeof(int*));


    while ( !feof(fichier) {
        tableau = realloc(tableau, (*total + 1) * sizeof(int*)); //  agrandit d'une ligne
        tableau[*total] = malloc(2 * sizeof(int)); // agrandit de deux colonnes


        if (condition == 1) {
            double variable_temporaire = 0.001;
            fscanf(fichier, "%lf", &variable_temporaire);
            tableau[*total][1] = (int)(variable_temporaire * 1000);
        } else {
            fscanf(fichier, "%d", &(tableau[*total][1]));
        }


        (*total)++;



    }
    printf("???");





    fclose(fichier);
    return tableau;
}*/
int** remplir_sommet(char* fname, int* tot, int cond){
    FILE* fichier = fopen(fname, "rw+");
    *tot = 0;


    int** tab = (int**) malloc( sizeof(int*) );


    while(!feof(fichier)){
        tab = (int**) realloc( tab, (*tot+1)*sizeof(int*) );

        tab[*tot] = (int*) malloc( 2*sizeof(int) );
        if(cond) {
            double temp = 0.001;
            fscanf(fichier, "%d %lf\n", &(tab[*tot][0]), &(temp));
            tab[*tot][1] = (int) (temp * 1000);
        }
        else{
            fscanf(fichier, "%d %d\n", &(tab[*tot][0]), &(tab[*tot][1]));
        }
        (*tot)++;
    }
    fclose(fichier);
    printf("\n");
    return tab;
}

void afficher_sommet (t_sommet info_sommet){

    printf("Precedences :\n");
    for(int i = 0; i < info_sommet.nbr_total_precedences; i++){
        printf("%d :\t%d\t%d\n", i, info_sommet.precedences[i][0], info_sommet.precedences[i][1]);
    }
    printf("\n");

    printf("Exclusions :\n");
    for(int i = 0; i < info_sommet.nbr_total_exclusions; i++){
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

    
void liberer_memoire ( t_sommet info_sommet){
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

