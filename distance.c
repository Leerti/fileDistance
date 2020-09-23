//
//  distance.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#include "distance.h"


#include "timer.h"
#include "levenshteindistance.h"
#include "iofile.h"
#include <stdio.h>
#include <stdlib.h>

void getDistance (char *firstFile, char *secondFile) {
    start_time();
    char *firstString = fileToString(firstFile);
    char *secondString = fileToString(secondFile);
    int distance = calculateLevenshtein(firstString, secondString);
    printf("\nEDIT DISTANCE: %i \n", distance);
    free(firstString);
    free(secondString);
    printf("TIME: %lf \n", end_time());
}


void getCommand(char *firstFile, char *secondFile, char *fOutput){
    start_time();
    char *firstString = fileToString(firstFile);
    char *secondString = fileToString(secondFile);
    generateModFile(getOperations(firstString,secondString), fOutput);
    free(firstString);
    free(secondString);
    printf("TIME: %lf\n", end_time());
}

void applyMod(char *fInput, char *fModify, char *fOutput){
    start_time();
    modifyFile(fInput,fModify,fOutput);
    printf("TIME: %lf\n", end_time());

}

