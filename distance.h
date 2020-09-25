
//  distance.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#ifndef distance_h
#define distance_h

#include <stdio.h>

/**
 *Questa funzione fa partire il timer e richiama le funzioni necessarie per calcolare la distanza di
 * Levenshtein tra i due file i cui path vengono presi in input.
 *Il timer viene fermato non appena la funzione pe ril calcolo della distanza di edit restituisce un valore.
 *Viene stampato a video la distanza e il tempo necessario per calcolarla.
 */
void getDistance(char *firstFile, char *secondFile);


/**
 *Questa funzione prende in input i path di tre file:
 *sui primi due file viene calcolata la distanza di edit e nel terzo vengono scritte le modifche necessarie a trasformare il secondo file nel primo.
 */
void getCommand(char *firstFile, char *secondFile, char *fOutput);


/**
 * Questa funzione prende in input tre file :
 * il primo è il file di partenza
 * il seondo è il file che continene le modifiche da applicare alla stringa contenuta nel file di partenza
 * il terzo è il file dove viene salvata la stringa modificata.
 */
void applyMod(char *fInput, char *fModify, char *fOutput);

/*
Function that returns the files contained in directory (and in
its subdirectory) which have minimum distance from fInput.
 */
void search(char *fInput, char *directory);

/*
Function that returns all files contained in directory (and in
its subdirectories) that have a limit of less than or equal to the fInput.
 */
void searchAll(char *fInput, char *directory, int limit);

#endif /* distance_h */
