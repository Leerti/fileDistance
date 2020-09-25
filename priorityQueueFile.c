//
//  stackFile.c
//  fileDistance
//
//  Created by Alessandra Lerteri Caroletta on 22/09/20.
//

#include "priorityQueueFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
Questa funzione viene richiamata dalla funzione ENQUEUENODE per allocare la memoria necessaria a contenere un nuovo nodo della coda.
 */
queueFile *newNodeFile(){
    queueFile *queueNode =(queueFile*)malloc(sizeof(queueFile));
    queueNode->distance = 0;
    queueNode->path = (char*) malloc(sizeof(char));
    queueNode->next = NULL;
    return queueNode;
}


/*
 Questa funzione viene richiamata da ENQUEUENODE per inserire il nodo nella giusta posizione.
 */
void insertNode(queueFile **root, queueFile *newNode){
    queueFile *head = *root;
    if(checkEmptyQueue(*root)){
        *root = newNode;
        return;
    }
    if(head->distance > newNode->distance){
        newNode->next = *root;
        *root = newNode;
    }else{
        while(head->next != NULL && head->next->distance < newNode->distance)
            head = head->next;
        newNode->next = head->next;
        head->next = newNode;
    }
}

void enqueueFile(queueFile **root, char *path, unsigned int distance){
    queueFile *newNode = newNodeFile();
    newNode->distance = distance;
    newNode->path = realloc(newNode->path, strlen(path));
    newNode->path = path;
    insertNode(root, newNode);
    
}

void dequeueFile(queueFile **root){
    queueFile *tmp = *root;
    if(!checkEmptyQueue(*root)){
        *root = (*root)->next;
        free(tmp);
    }
}

int checkEmptyQueue(queueFile *root){
    if(root!=NULL){
        return 0;
    }
  return 1;
}

