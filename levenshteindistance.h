//
//  levenshteindistance.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#ifndef levenshteindistance_h
#define levenshteindistance_h


#include <stdio.h>
#include "stackCommand.h"

/*
 *Questa funzione prend ein input due stringhe e calcola la distanza di edit tra le due.
 *Viene utilizzato l'algoritmo di Levenshtein ottimizzato:
 *Invece di utilizzare una matrice m*n (dove m-1 è la lunghezza della prima stringa e n-1 è la lunghezza della seconda stringa,
 *viene utilizzata una matrice 2*n.
 */
int calculateLevenshtein(char *firstString, char *secondString);


/**
 *La funzione restituisce uno Stack contenente le operazioni da eseguire per trasformare la seconda Stringa nella prima
 */
Stack *getOperations (char *firstString, char *secondString);


void recursiveLevensthein(char *fInput, char *path, unsigned int distanceLimit);




#endif /* levenshteindistance_h */
