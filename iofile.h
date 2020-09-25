//
//  iofile.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#ifndef iofile_h
#define iofile_h

#include <stdio.h>
#include "stackCommand.h"


/*
  Funzione utilizzata per convertire una sequenza di caratteri in  un file.
 */
void stringToFile(char *fileOutput, char *string);


/*
  Funzione per convertire qualsiasi tipo di file in una sequenza di caratteri.
 */
char *fileToString(char *fileInput);


/*
 Funzione che, preso uno Stack e un file (binario), scrive le operazioni dello stack con corrispettiva
 posizione e carattere (a  meno che non si tratti della DEL, in cui non è presente in carattere) sul
 file in forma binaria.
 */
void writeModFile(stackCommand *stack, char *fileOutput);


/*
 Funzione che prende n input un file iniziale, un file in cui sono scritte le modifiche da apportare e
 un file in cui scrivere il contenuto del file iniziale modificato con le azioni scritte nel secondo file.
 Il file in cui sono contenute le azioni è un file binario.
 Questa funzione si serve di un altro metodo, chiamato ReadModFile che  legge il contenuto del file
 in cui sono scritte le modifiche e ritorna uno Stack.
 Dallo Stack, la funzione applyModToFile applica le modifiche al file in input e genera il file di output
 */
void applyModToFile(char *fileInput, char *fileModify, char *fileOutput);


#endif /* iofile_h */
