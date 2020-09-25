//
//  iofile.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#include "iofile.h"


#include "stackCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *Funzione per eseguire l'operazione SET nella posizione 'pos' del carattere 'character'.
 *Viene settato il carattere presente nella posizione 'pos' come 'character'
 */
char *set(char *string, unsigned int position, char character) {
    position--;
    string[position] = character;
    return string;
}


/*
 *Funzione per eseguire l'operazione DEL nella posiozne 'pos'.
 *Dalla posizione pos alla fine dela stringa vengono spostati tutti i caratteri indietro di una posizione.
 *L'ultimo carattere presente viene sovrascritto con '\0' (carattere di terminazione della stringa).
 */
char *del(char *string, unsigned int position) {
    position--;
    while(position<strlen(string)-1){
        string[position]=string[position+1];
        position++;
    }
    string[position]='\0';
    
    return string;
}


/*
 *Funzione per eseguire l'operazione ADD del carattere 'character' nella posizione 'pos'.
 *Vengono copiati tutti i caratteri dall'inizio della stringa fino alla poszione 'pos'-1 in un'altra stringa[temp],
 * viene aggiunto il carattere 'character' e tutti gli altri caratteri (dalla posizione 'pos' alla fine della stringa) vengono
 * riscritti dopo.
 *La funzione ritorna il puntatore a caratteri che contiene la nuova stringa con il carattere aggiunto.
 */
char *add(char *string, unsigned int position, char character) {
    int i;
    unsigned int length;
    char *temp = NULL;
    if (string) {
        length = (int)strlen(string);
    } else length = 0;
    temp = (char *) calloc(1,length + 2);
    if (temp != NULL) {
        if (position > length) {
            position = length;
        }
        for (i = 0; i < position; i++) {
            temp[i] = string[i];
        }
        temp[i] = character;
        while(i < length) {
            temp[i + 1] = string[i];
            i++;
        }
        temp[i + 1] = '\0';
        free(string);
    }
    return temp;
}


/*
 *Questa funzione prende in input un puntatore a puntatore ad uno stack, un carattere 'command' che indica il comando da
 * eseguire (A,per ADD-S,per SET-D, per DEL), un intero senza segno che indica la posizione dove la modifica deve essere
 * fatta, 'pos', e il carattere da modificare 'character'.
 *La funzione richiama il metodo PUSHNODE per creare ed inserire un nuovo nodo all'interno dello Stack che ha come radice root.
 */
void pushOperationInStack(Stack **root, char command, unsigned int position, char character) {
    if(command=='S'){
            pushCommand(root,  position, character,SET);
    }else if(command=='A'){
            pushCommand(root, position, character, ADD);
    }else{
        pushCommand(root, position, character, DEL);
    }
}


/*
 *Questa funzione prende in input il path del file in cui sono scritte le operazioni di modifica nella forma:
 *ADD​nb​: n è un intero senza segno (unsigned int) rappresentato con 4 byte (byte più significativo all’inizio)
 * mentre ​b è un singolo byte. Tale operazione indica che viene aggiunto il byte ​b n​ ella posizione ​n​.
 *DEL​n:​ n è un intero senza segno (unsigned int). Tale operazione indica che viene eliminato il byte​ n​ ella posizione ​n.
 *SET​nb​: n è un intero senza segno (unsigned int) rappresentato con 4 byte mentre ​b è un singolo byte. Tale operazione indica
 * che valore del byte in posizione ​n ​viene impostato a ​b.
 *La funzione legge le operazioni dal file e le aggiunge attraverso la funzione PUSHOPERATIONINSTACK allo Stack.
 */
Stack *readModFile(char *fileModify) {
    FILE *fileBin = fopen(fileModify, "rb");
    if (fileBin == NULL) {
        perror("Could not open file");
        exit(1);
    }
    Stack *root = NULL;
    char command;
    unsigned int position;
    char character ='\0';
    while (feof(fileBin)==0) {
        fread(&command, sizeof(char), 1, fileBin);
        fseek(fileBin, 2, SEEK_CUR);
        fread(&position, (sizeof( unsigned int)), 1, fileBin);
        if(command!='D')
        fread(&character, (sizeof(char)), 1, fileBin);
        pushOperationInStack(&root, command, position, character);
    }
    popCommand(&root);
    fclose(fileBin);
    return root;
}


char *fileToString(char *fileInput) {
    FILE *fileIn = fopen(fileInput, "r+");
    if (fileIn == NULL) {
        perror("Could not open file");
        exit(1);
    }
    fseek(fileIn, 0, SEEK_END);
    long length = ftell(fileIn);
    rewind(fileIn);
    char *str = (char *) calloc(1,length);
    if (str != NULL) {
        fread(str, length, 1, fileIn);
    }
    fclose(fileIn);
    return str;
}


void stringToFile(char *fileOutput, char *string) {
    FILE *fileOut = fopen(fileOutput, "w+");
    if (fileOut == NULL) {
        perror("Could not open file");
        exit(1);
    }
    fputs(string, fileOut);
    fclose(fileOut);
}


void writeModFile(Stack *stack, char *fileOutput) {
        FILE *filebin;
        if ((filebin = fopen(fileOutput, "w+b")) == NULL) {
            perror("Could not open file");
            exit(1);
        }else{
            char* command=NULL;
            while(!checkEmptyCommandStack(stack)){
                command=getType(stack);
                for (int i=0;i<3;i++){
                    fwrite(&command[i], 1 ,sizeof(char),filebin);
                }
                fwrite(&stack->pos,1,sizeof(unsigned int),filebin);
                if(strcmp("DEL",command)!=0)
                fwrite(&stack->character,1,sizeof(char),filebin);
                popCommand(&stack);
            }
            popCommand(&stack);
            fclose(filebin);
        }
}





void applyModToFile(char *fileInput, char *fileModify, char *fileOutput) {
    Stack *root = readModFile(fileModify);
    char *stringInput = fileToString(fileInput);
    while (!checkEmptyCommandStack(root)) {
        type_op type = root->type;
        if (type == SET)
            stringInput = set(stringInput, root->pos, root->character);
        else if (type == DEL)
            stringInput = del(stringInput, root->pos);
        else
            stringInput = add(stringInput, root->pos, root->character);
        popCommand(&root);
    }
    stringToFile(fileOutput, stringInput);
}
