//
//  stackCommand.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#ifndef stackCommand_h
#define stackCommand_h

#include <stdio.h>

typedef enum {
    ADD,
    DEL,
    SET
}
        type_op;


typedef struct Stack_command {
    unsigned int pos;
    char character;
    type_op type;
    struct Stack_command *prev;
}
        Stack;

void pushNode(Stack **root, unsigned int pos, char character, type_op type);

void popNode(Stack **root);

char *getType(Stack *node);

int checkEmptyStack(Stack*);

#endif /* stackCommand_h */
