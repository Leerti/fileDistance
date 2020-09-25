//
//  stackFile.h
//  fileDistance
//
//  Created by Alessandra Lerteri Caroletta on 22/09/20.
//

#ifndef stackFile_h
#define stackFile_h

#include <stdio.h>

typedef struct queue_file{
    char *path;
    int distance;
    struct queue_file *next;
    }queueFile;


/*
Funzione per controllare se la coda sia vuota.
 La funzione restituisce 0 finche ci sono elementi all'interno
*/
int checkEmptyQueue(queueFile *root);


/*
Funzione per aggiungere un elemento alla coda con priorità.
Essendo una coda con priorità, l'elemento aggiunto non viene aggiunto in testa ma in una determinata posizione.
 La sua priorità nella coda è determinata dalla distanza.
 Più la distanza è piccola, più sarà 'in alto' nella coda
*/
void enqueueFile(queueFile **root, char *path, unsigned int distance);


/*
Questa funzione rimuove il nodo della coda con maggiore priorità: cioè il nodo che sta più 'in alto '.
*/
void dequeueFile(queueFile **root);


#endif /* stackDirectory_h */
