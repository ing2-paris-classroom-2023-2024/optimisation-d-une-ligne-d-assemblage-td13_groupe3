#include "header.h"

t_sommet recuperer_info_sommet(char* info_identifiant) {
    t_sommet info_sommet;
    char chaine_temporaire[100];

    // Chargement des données de précédence
    sprintf(chaine_temporaire, "../fichiers_ressources/%s/precedences.txt", info_identifiant);
    info_sommet.precedences = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_precedences), 0);

    // Chargement des données d'opération
    sprintf(chaine_temporaire, "../fichiers_ressources/%s/operations.txt", info_identifiant);
    info_sommet.operations = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_operations), 0);

    // Chargement des données d'exclusions

    sprintf(chaine_temporaire, "../fichiers_ressources/%s/exclusions.txt", info_identifiant);
    info_sommet.exclusions = remplir_sommet(chaine_temporaire, &(info_sommet.nbr_total_exclusions), 1);

    // Chargement du temps de cycle
    sprintf(chaine_temporaire, "../fichiers_ressources/%s/temps_cycle.txt", info_identifiant);
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

int** remplir_sommet(char* nom_fichier, int* total, int condition) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    *total = 0;
    int** tableau = NULL;
    while (fscanf(fichier, "%d", &(tableau[*total][0])) != EOF) {
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

    fclose(fichier);
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

int main(){
    char* info
    
}