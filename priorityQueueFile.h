//
//  stackFile.h
//  fileDistance
//
//  Created by Alessandra Lerteri Caroletta on 22/09/20.
//

#ifndef stackFile_h
#define stackFile_h

#include <stdio.h>

typedef struct StackFile{
    char *path;
    int distance;
    struct StackFile *next;
}StackFile;

StackFile *newQueueList(void);

/*
Function to check if the stack is empty
*/
int checkEmptyFileStack(StackFile *root);

/*
Function to add an item to the priority stack: "root".
(priority is determined by distance)
*/
void enqueueFile(StackFile **root, char *path, unsigned int distance);

/*
Function toremove a lower priority item
(from the start) from the stack: "root".
*/
void dequeueFile(StackFile **root);


#endif /* stackDirectory_h */
