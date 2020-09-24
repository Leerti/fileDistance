//
//  iofile.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#include "iofile.h"

#include "stackCommand.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 Function to execute a SET in the string: "string" in
 the position: "pos" of the character: "character".
 */
char *set(char *string, unsigned int pos, char character) {
    pos = pos - 1;
    string[pos] = character;
    return string;
}

/*
Function to execute a DEL in the string: "string" in the position: "pos"
 */
char *del(char *string, unsigned int pos) {
    pos--;
    while(pos<strlen(string)-1){
        string[pos]=string[pos+1];
        pos++;
       
    }
    string[pos]='\0';
    
    return string;
}

/*
Function to execute an ADD in the string: "string"
in the position: "pos" of the character: "character"
 */
char *add(char *string, unsigned int pos, char character) {
    int i;
    unsigned int length;
    char *temp = NULL;
    if (string) {
        length = (int)strlen(string);
    } else length = 0;
    temp = (char *) malloc(length + 2);
    if (temp != NULL) {
        if (pos > length) {
            pos = length;
        }
        for (i = 0; i < pos; i++) {
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


char *fileToString(char *fileInput) {
    FILE *fileIn = fopen(fileInput, "r");
    if (fileIn == NULL) {
        perror("Could not open file");
        exit(1);
    }
    fseek(fileIn, 0, SEEK_END);
    long length = ftell(fileIn);
    rewind(fileIn);
    char *str = (char *) malloc(length);
    if (str != NULL) {
        fread(str, length, 1, fileIn);
    }
    fclose(fileIn);
    return str;
}


void stringToFile(char *fileOutput, char *string) {
    FILE *fileOut = fopen(fileOutput, "w");
    if (fileOut == NULL) {
        perror("Could not open file");
        exit(1);
    }
    fputs(string, fileOut);
    fclose(fileOut);
}


void writeModFile(Stack *stack, char *fileOutput) {
        FILE *filebin;
        if ((filebin = fopen(fileOutput, "wr+")) == NULL) {
            perror("Could not open file");
            exit(1);
        }else{
            char* command=NULL;
            while(!checkEmptyStack(stack)){
                command=getType(stack);
                for (int i=0;i<3;i++){
                    fwrite(&command[i], 1 ,sizeof(char),filebin);
                }
                fwrite(&stack->pos,1,sizeof(unsigned int),filebin);
                if(strcmp("DEL",command)!=0)
                fwrite(&stack->character,1,sizeof(char),filebin);
                popNode(&stack);
            }
            popNode(&stack);
            fclose(filebin);
        }
}


void pushOperationInStack(Stack **root, char command, unsigned int position, char character) {
    if(command=='S'){
            pushNode(root,  position, character,SET);
    }else if(command=='A'){
            pushNode(root, position, character, ADD);
    }else{
        pushNode(root, position, character, DEL);
    }
}

/*
Function to read a stack of instructions from a .bin file
 */
Stack *readModFile(char *fModify) {
    FILE *fileBin = fopen(fModify, "rb");
    if (fileBin == NULL) {
        perror("Could not open file");
        exit(1);
    }
    Stack *root = NULL;
    char command;
    unsigned int position;
    char character ='\0';
    while (!feof(fileBin)) {
        fread(&command, sizeof(char), 1, fileBin);
        fseek(fileBin, 2, SEEK_CUR);
        fread(&position, (sizeof( unsigned int)), 1, fileBin);
        if(command!='D')
        fread(&character, (sizeof(char)), 1, fileBin);
        pushOperationInStack(&root, command, position, character);
        character='\0';
    }
    fclose(fileBin);
    return root;
    
}

void modifyFile(char *fileInput, char *fileModify, char *fileOutput) {
    Stack *root = readModFile(fileModify);
    char *stringInput = fileToString(fileInput);
    while (!checkEmptyStack(root)) {
        type_op type = root->type;
        if (type == SET)
            stringInput = set(stringInput, root->pos, root->character);
        else if (type == DEL)
            stringInput = del(stringInput, root->pos);
        else
            stringInput = add(stringInput, root->pos, root->character);
        popNode(&root);
    }
    stringToFile(fileOutput, stringInput);
}

