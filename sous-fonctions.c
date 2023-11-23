//
// Created by alang on 23/11/2023.
//
#include "header.h"

// nous souhaitons récupérer les données des fichiers
t_sommet recuperer__info_sommet(char* info_identifiant){
    t_sommet info_sommet;
    char* chaine_temporaire = (char*) malloc ( 100* sizeof (char)); // allocation dynamique


    // Chargement des données de précédence
    strcpy(chaine_temporaire, "../fichiers_ressources/"); // ajoute le contenu du fichier dans la chaine temporaire
    strcat(chaine_temporaire, info_identifiant); // ajoute l'identifiant dans la chaine temporaire
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "precedences"); // ajoute le fait qu'il s'agit d'une précédence dans la chaine temporaire
    strcat(chaine_temporaire, ".txt");
    info_sommet.precedences = remplir_sommet(); /** modifier les paramètres **/

    // Chargement des données d'opération
    strcpy(chaine_temporaire, "../fichiers_ressources/");
    strcat(chaine_temporaire, info_identifiant);
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "operations");
    strcat(chaine_temporaire, ".txt");
    info_sommet.operations = remplir_sommet(); /** modifier les paramètres **/

    // Chargement des données d'exclusions
    strcpy(chaine_temporaire, "../fichiers_ressources/");
    strcat(chaine_temporaire, info_identifiant);
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "exclusions");
    strcat(chaine_temporaire, ".txt");
    info_sommet.operations = remplir_sommet(); /** modifier les paramètres **/



    // Chargement du temps de cycle
    strcpy(chaine_temporaire, "../fichiers_ressources/");
    strcat(chaine_temporaire, info_identifiant);
    strcat(chaine_temporaire, "/");
    strcat(chaine_temporaire, "temps_cycle");
    strcat(chaine_temporaire, ".txt");
    FILE* fichier = fopen(chaine_temporaire, "rw+");
    if (!feof(fichier)) //feof est la fin du fichier
        fscanf(fichier, "%d\n", &(info_sommet.temps_operation));
    info_sommet.temps_operation *= 1000; // on multiplie par 1000 afin de ne pas avoir de float
    fclose(fichier);
}