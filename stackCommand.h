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


typedef struct stack_command {
    unsigned int pos;
    char character;
    type_op type;
    struct stack_command *prev;
}
        stackCommand;


/*
 Funzione per inserire un nodo all'interno dello stack.
 Prende in input un puntatore a puntatore dello Stack(la root), un intero senza segno(indica la posizione in cui "modificare" il carattere), un carattere(il carattere da aggiungere o da modificare, se la modifica è DEL, il carattere passato è '\0')  e una variabile ti tipo type_op(che definisce il tipo di operazione da fare: DELL, ADD, SET).
 */
void pushCommand (stackCommand **root, unsigned int pos, char character, type_op type);


/*
 Funzione per rimuovere un nodo dallo Stak.
 Prende in input un puntatore a puntatore allo stack e, se esiste almeno un nodo dealloca la memoria del nodo in testa , quando lo stack è vuoto dealloca la memoria del puntatore stesso allo stack.
 */
void popCommand (stackCommand **root);


/*
 Preso in input un nodo, restituisce il tipo dell'operazione che contiene.
 */
char *getType (stackCommand *node);


/*
 Verifica se lo stack è vuoto o ci sono ancora elementi.
 Il valore di ritorno della funzione è 0 finche ci sono ancora elementi.
 */
int checkEmptyCommandStack (stackCommand *root);


#endif /* stackCommand_h */
