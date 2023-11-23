#include "header.h"

// nous souhaitons récupérer les données des fichiers
t_sommet recuperer__info_sommet(char* info_identifiant){
    t_sommet info_sommet;
    char* chaine_temporaire = malloc ( 100* sizeof (char)); // allocation dynamique


    // Chargement des données de précédence
    strcat(chaine_temporaire, info_identifiant); // ajoute l'identifiant dans la chaine temporaire
    strcpy(chaine_temporaire, "../fichiers_ressources/"); // ajoute le contenu du fichier dans la chaine temporaire
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "precedences"); // ajoute le fait qu'il s'agit d'une précédence dans la chaine temporaire
    strcat(chaine_temporaire, ".txt");
    info_sommet.precedences = remplir_sommet(chaine_temporaire, info_sommet.nbr_total_precedences, 0); /** modifier les paramètres **/

    // Chargement des données d'opération
    strcat(chaine_temporaire, info_identifiant);
    strcpy(chaine_temporaire, "../fichiers_ressources/");
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "operations");
    strcat(chaine_temporaire, ".txt");
    info_sommet.operations = remplir_sommet(chaine_temporaire, info_sommet.nbr_total_operations, 0); /** modifier les paramètres **/

    // Chargement des données d'exclusions
    strcat(chaine_temporaire, info_identifiant);
    strcpy(chaine_temporaire, "../fichiers_ressources/");
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "exclusions");
    strcat(chaine_temporaire, ".txt");
    info_sommet.operations = remplir_sommet(chaine_temporaire, info_sommet.nbr_total_exclusions, 1); /** modifier les paramètres **/

    // Chargement du temps de cycle
    strcat(chaine_temporaire, info_identifiant);
    strcpy(chaine_temporaire, "../fichiers_ressources/");
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "temps_cycle");
    strcat(chaine_temporaire, ".txt");
    FILE* fichier = fopen(chaine_temporaire, "rw+");
    if (!feof(fichier)) //feof est la fin du fichier
        fscanf(fichier, "%d\n", &(info_sommet.temps_operation));
    info_sommet.temps_operation *= 1000; // on multiplie par 1000 afin de ne pas avoir de float
    fclose(fichier);
}


int** remplir_sommet(char* nom_fichier, int* total, int condition){

    FILE* fichier = fopen(nom_fichier, "rw+");
    *total = 0;
    int** tableau = malloc(sizeof(int*) );
    while(!feof(fichier)){
        tableau = realloc(tableau, (*total + 1) * sizeof(int*) );
        tableau[*total] = malloc(10 * sizeof(int) );
        if(condition) {
            double variable_temporaire = 0.001;
            fscanf(fichier, "%d %lf\n", &(tableau[*total][0]), &(variable_temporaire));
            tableau[*total][1] = (int) (variable_temporaire * 1000);
        }
        else{
            fscanf(fichier, "%d %d\n", &(tableau[*total][0]), &(tableau[*total][1]));
        }
        (*total)++; // incrémentation
    }
    fclose(fichier);
    return tableau;

}

