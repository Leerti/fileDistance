//
//  stackCommand.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#include "stackCommand.h"

#include <stdlib.h>
#include <string.h>


/*
 Funzione utilizzata per creare un nuovo nodo.
 Viene richiamata dalla funzione pushNode per allocare la memoria necessaria a contenere uno Stack.
 */
stackCommand *createNewNode () {
    stackCommand *newNode = (stackCommand *) calloc(1,sizeof(stackCommand));
    newNode->pos = 0;
    newNode->character = ' ';
    newNode->type = 0;
    newNode->prev = NULL;
    return newNode;
}


void pushCommand (stackCommand **root, unsigned int pos, char character, type_op type) {
    stackCommand *nextNode = createNewNode();
    nextNode->pos = pos;
    nextNode->character = character;
    nextNode->type = type;
    nextNode->prev = *root;
    *root = nextNode;
}


void popCommand (stackCommand **root) {
    stackCommand * temp= *root;
    if(!checkEmptyCommandStack(*root)){
        *root = (*root)->prev;
      
        free(temp);
    }else {
       
        free(*root);
    }
}


char *getType (stackCommand *node) {
    if(!checkEmptyCommandStack(node)){
        switch (node->type) {
            case SET:
                return "SET";
            case ADD:
                return "ADD";
            case DEL:
                return "DEL";
        }
    }
    else return "0";
}


int checkEmptyCommandStack (stackCommand *root) {
    if(root!=NULL){
        return 0;
    }
  return 1;
}

