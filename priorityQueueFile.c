//
//  stackFile.c
//  fileDistance
//
//  Created by Alessandra Lerteri Caroletta on 25/09/20.
//

#include "priorityQueueFile.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Function to create a new node to add to the stack.
 */
StackFile *newNodeFile(){
    StackFile *queueNode =(StackFile*)malloc(sizeof(StackFile));
    queueNode->distance = 0;
    queueNode->path = (char*) malloc(sizeof(char));
    queueNode->next = NULL;
    return queueNode;
}

int checkEmptyFileStack(StackFile *root){
    if(root!=NULL){
        return 0;
    }
  return 1;
}

void insertNode(StackFile **root, StackFile *newNode){
    StackFile *head = *root;
    if(checkEmptyFileStack(*root)){
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

void enqueueFile(StackFile **root, char *path, unsigned int distance){
    StackFile *newNode = newNodeFile();
    newNode->distance = distance;
    newNode->path = realloc(newNode->path, strlen(path));
    newNode->path = path;
    insertNode(root, newNode);
    
}

void dequeueFile(StackFile **root){
    StackFile *tmp = *root;
    if(!checkEmptyFileStack(*root)){
        *root = (*root)->next;
        free(tmp);
    }
}
