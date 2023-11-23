//
// Created by alang on 22/11/2023.
//

#ifndef ECELECAR_HEADER_H
#define ECELECAR_HEADER_H


typedef struct sommet {

    int** exclusions; //  pointeur vers un pointeur
    int** precedences; // utilisé pour stocker l'adresse d'un tableau de pointeurs d'entiers
    int** operations;
    int nbr_total_exclusions;
    int nbr_total_precedences;
    int nbr_total_operations;

};

#endif //ECELECAR_HEADER_H
