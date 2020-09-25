//
//  stackCommand.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
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


/**
 Funzione per inserire un nodo all'interno dello stack.
 Prende in input un puntatore a puntatore dello Stack(la root), un intero senza segno(indica la posizione in cui "modificare" il carattere), un carattere(il carattere da aggiungere o da modificare, se la modifica è DEL, il carattere passato è '\0')  e una variabile ti tipo type_op(che definisce il tipo di operazione da fare: DELL, ADD, SET).
 */
void pushCommand (Stack **root, unsigned int pos, char character, type_op type);


/**
 Funzione per rimuovere un nodo dallo Stak.
 Prende in input un puntatore a puntatore allo stack e, finche esistono nodi dealloca la memoria del nodo, quando lo stack è vuoto dealloca la memoria del puntatore stesso allo stack.
 */
void popCommand (Stack **root);


/**
 Preso in input un nodo, restituisce il tipo dell'operazione che contiene.
 */
char *getType (Stack *node);


/**
 Verifica se lo stack è vuoto o ci sono ancora elementi.
 Il valore di ritorno della funzione è 0 finche ci sono ancora elementi.
 */
int checkEmptyCommandStack (Stack *root);


#endif /* stackCommand_h */
