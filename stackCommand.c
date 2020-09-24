//
//  stackCommand.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#include "stackCommand.h"


#include <stdlib.h>
#include <string.h>


int checkEmptyStack(Stack *root) {
    return !root;
}
Stack *createNewNode() {
    Stack *newNode = (Stack *) malloc(sizeof(Stack));
    newNode->pos = 0;
    newNode->character = ' ';
    newNode->type = 0;
    newNode->prev = NULL;
    return newNode;
}

void pushNode(Stack **root, unsigned int pos, char character, type_op type) {
    Stack *nextNode = createNewNode();
    nextNode->pos = pos;
    nextNode->character = character;
    nextNode->type = type;
    nextNode->prev=*root;

    *root = nextNode;
}

void popNode(Stack**root){
    Stack * temp= *root;
    if(!checkEmptyStack(*root)){
        *root = (*root)->prev;
        
        free(temp);
    }else {
        free(*root);
    }
}

char *getType(Stack *node){
    if(!checkEmptyStack(node)){
        switch (node->type) {
            case SET:
                return "SET";
            case ADD:
                return "ADD";
            case DEL:
                return "DEL";
        }
    }
    else return "No more operation";

}



