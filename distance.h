
//  distance.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#ifndef distance_h
#define distance_h

#include <stdio.h>


/*
 Questa funzione fa partire il timer e richiama le funzioni necessarie per calcolare la distanza di Levenshtein tra i due file i cui path vengono presi in input.
 Il timer viene fermato non appena la funzione pe ril calcolo della distanza di edit restituisce un valore.
 Viene stampato a video la distanza e il tempo necessario per calcolarla.
 */
void getDistance(char *firstFile, char *secondFile);


/*
 Questa funzione prende in input i path di tre file: sui primi due file viene calcolata la distanza di edit e nel terzo vengono scritte le modifche necessarie a trasformare il secondo file nel primo.
 */
void getCommand(char *firstFile, char *secondFile, char *fOutput);


/*
  Questa funzione prende in input tre file :
  il primo è il file di partenza
  il seondo è il file che continene le modifiche da applicare alla stringa contenuta nel file di partenza
  il terzo è il file dove viene salvata la stringa modificata.
 */
void applyMod(char *fileInput, char *fileModify, char *fileOutput);


/*
Questa funzione prende in input un file e una directory e utilizza lo standardOutput per produrre i file contenuti in dir (e nelle sue sottodirectory) che hanno minima distanza da fileInput.
 */
void search(char *fileInput, char *directory);


/*
Questa funzione prende in input un file, una directory e un intero e visualizza tutti i file presenti nella directory e nelle sue sottodirectory che hanno distanza di edit uguale o inferiore al limite.
 */
void searchAll(char *fileInput, char *directory, int limit);

#endif /* distance_h */
