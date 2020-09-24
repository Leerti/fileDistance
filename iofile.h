//
//  iofile.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#ifndef iofile_h
#define iofile_h

#include <stdio.h>

#include "stackCommand.h"

/**
 * Funzione utilizzata per convertire una sequenza di caratteri ijn un file.
 * Utilizzata per scrivere su di un file.
 *
 */
void stringToFile(char *fileOutput, char *string);

/**
 * Funzione per convertire qualsiasi tipo di file in una sequenza di caratteri.
 * Utilizzata per leggere un file.
 */
char *fileToString(char *fileInput);

void writeModFile(Stack *stack, char *fileOutput);

void modifyFile(char *fileInput, char *fileModify, char *fileOutput);

Stack *readModFile(char *fModify);

#endif /* iofile_h */
