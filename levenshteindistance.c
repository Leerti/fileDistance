//
//  levenshteindistance.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#include "levenshteindistance.h"


#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "stackCommand.h"
#include "priorityQueueFile.h"


/*
 *Funzione che calcola il minimo tra tre numeri
 */
int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}


/*
 *Controlla se la lunghezza di una delle due stringhe è 0. in questo caso la distanza di edit è pari alla lunghezza dell'altra
 * stringa.
 *Se entrambe le stringhe hanno almeno un carattere, la funzione ritorna 0.
 */
int checkNull(int x, int y) {
    if (x == 0) {
        return y;
    } else if (y == 0) {
        return x;
    }
    return 0;
}


/*
 *Funzione che calcola il valore di un elemento della matrice.
 *L'elemento viene calcolato come il minimo tra l'emento nella riga precende e stessa colonna (aboveEl) +1, l'elemento nella
 * colonna precente e stessa riga (leftEl) +1  e l'elemento nella riga precende e nella colonna precedente (diagonalEl) + cost.
 *Cost è uguale a 0 se e solo se i caratterie della seconda e prima stringa corrispondenti rispettivamente alla riga(-1) e alla
 * colonna(-1) dell'elemento da calcolare, sono uguali
 */
int calculateElement(int aboveEl, int leftEl, int diagonalEl, char firstStringChar, char secondStringChar) {
    int cost = 0;
    if (firstStringChar != secondStringChar) {
        cost = 1;
    }
    int el = min(diagonalEl + cost, aboveEl + 1, leftEl + 1);
    return el;
}


/*
 *Funzione che presa in input una matrice m*n ne calcola gli elementi richiamando la funzione CALCULATEELEMENT
 */
void initMatrix(int **matrix, char *firstString, int x, char *secondString, int y) {
    for (int i = 1; i < x; i++) {
        for (int j = 1; j < y; j++) {
            matrix[i][j] = calculateElement(matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1], firstString[i-1], secondString[j-1]);
        }
    }
}


/*
 *Funzione che prese in input due strighe di lunghezza m-1 ed n-1, alloca l'alrea necessaria a contenere la matrice m*n.
 *Inizializza la matrice scrivendo nella prima righa 0...n e nella prima colonna 0...m
 */
int **createMatrix(char *firstString, char *secondString) {
    int x = (int) strlen(firstString) + 1;
    int y = (int) strlen(secondString) + 1;
    int **matrix = calloc(x, sizeof(int *));
    if (matrix != NULL)
        for (int i = 0; i < x; i++) {
            matrix[i] = calloc(y, sizeof(int));
        }
    for (int i = 0; i < x; i++) {
        matrix[i][0] = i;
    }
    for (int j = 1; j < y; j++) {
        matrix[0][j] = j;
    }
    initMatrix(matrix, firstString, x, secondString, y);
    return matrix;
}


/*
 *Funzione per deallocare la matrice passata in input
 */
void deallocateMatrix(int size, int **matrix) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


/*
 *Funzione che prende in input una matrice gia riempita  e le coordinate x, y
 *Per la casella con coordinate x,y calcola l'operazione da eseguire :ADD, DEL  o SET.
 *Se la casella di cui determinare l'operazione fa parte della prima riga il valore di ritorno è ADD( significa che la seconda
 *stringa è piu corta della prima e per trasformarla nella prima bisogna ggiungere caratteri)
 *Se la casella di cui determinare l'operazione fa parte della pirma colonna il valore di ritonro è DEL( significa che la prima
 *srtringa è piu corta della seconda e per trasfomrare la seocnda nella prima bisogna eliminare caratteri)
 */
type_op defineOperation(int**matrix, int x, int y) {
    if (x == 0) {
        return DEL;
    } else if (y == 0) {
        return ADD;
    } else {
        int minimum = min(matrix[x-1][y], matrix[x][y-1], matrix[x-1][y-1]);
        if (minimum == matrix[x-1][y-1]) {
            return SET;
        } else if (minimum ==matrix[x-1][y]) {
            return ADD;
        } else return DEL;

    }
}


/*
 *Queata funzione prende in input un 'type' che rappresenta il tipo dell'operazione, uno Stack, le due stringhe e i puntatori
 * alle  coordinate x,y.
 *Aggiunge allo stack un nuovo nodo composto dall'operazione in input, nella posizione contenuta nella variabile puntatta da y,
 * del carattere corrispondente alla poszione x-1 della prima stringa.
 *Nel caso in cui l'operazione da eseguire sia una SET, si controlla se i caratteri delle due stringhe rispettivamente nelle
 * posizione x-1 e y-1 sono diversi: solo in questo caso si esegue la SET, altrimenti non si esegue nulla.
 */
void pushOperation(type_op type, stackCommand **root, char *firstString, char *secondString, int *x, int *y) {
    if (type == SET) {
        if (firstString[*x - 1] != secondString[*y - 1]) {
            pushCommand(root, *y, firstString[*x - 1], SET);
        }
        (*x)--;
        (*y)--;
    } else if (type == DEL) {
        pushCommand(root, *y, ' ', DEL);
        (*y)--;
    } else if (type == ADD) {
        pushCommand(root, *y, firstString[*x - 1], ADD);
        (*x)--;
    }

}


int calculateLevenshtein(char *firstString, char *secondString) {
    int x = (int)strlen(firstString);
    int y = (int)strlen(secondString);
    int *prev = calloc(y + 1, sizeof(int));
    int *curr = calloc(y + 1, sizeof(int));
    int i, j, distance;
    distance = checkNull(x, y);
    if (!distance) {
        for (j = 0; j <= y; j++)
            prev[j] = j;
        for (i = 1; i <= x; i++) {
            curr[0] = i;
            for (j = 1; j <= y; j++) {
                curr[j] = calculateElement(prev[j], curr[j - 1], prev[j - 1], firstString[i - 1], secondString[j - 1]);
            }
            for (int k = 0; k <= y; k++)
                prev[k] = curr[k];
            for (int k = 1; k <= y; k++)
                curr[k] = 0;
        }
        distance = prev[y];
    }
    free(prev);
    free(curr);
    return distance;
}


stackCommand *getOperations(char *firstString, char *secondString) {
    int **matrix = createMatrix(firstString, secondString);
    int x = (int) strlen(firstString);
    int y = (int) strlen(secondString);
    stackCommand *stack = NULL;
    int currentPos = matrix[x][y];
    while (currentPos != 0) {
        pushOperation(defineOperation(matrix, x, y), &stack, firstString, secondString, &x, &y);
        currentPos = matrix[x][y];
    }
    deallocateMatrix(x+ 1, matrix);
    return stack;
}


/*
 Funzione per eseguire una visita in profondita partendo dalla direcotry base.
 Per ogni file incontrato si esegue un ENQUEUEFILE e il file viene aggiunto nella giusta posizione nella coda root.
*/
void depthSearch(char *fInput, char *base, queueFile **root){
    struct dirent *dp;
    DIR *directory = opendir(base);
    if(!directory)
        return;
    while((dp = readdir(directory)) != NULL){
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".DS_Store")){
            char *path = (char*)malloc((strlen(base)+strlen(dp->d_name)+1)*sizeof(char));
            strcpy(path, base);
            strcat(path, "/");
            strcat(path, dp->d_name);
            if(dp->d_type != DT_DIR)
                enqueueFile(root, path, calculateLevenshtein(fInput, path));
            else
                depthSearch(fInput, path, root);
        }
    }
    closedir(directory);
}

/*
Funzione per stampare a video una seuqenza di path di file con relativa distanza di edit.
 Gli unici file che vengono stampati sono quelli con distanza di edit minore di limit.
 */

void printQueuePath(queueFile **root, unsigned int distanceLimit){
    if(checkEmptyQueue(*root))
        return;
    queueFile *node = *root;
    if(distanceLimit==0)
        distanceLimit = (*root)->distance;
    while (!checkEmptyQueue(*root) && (node = *root)->distance <= distanceLimit) {
        char *path = realpath(node->path, NULL);
        printf("%i\t\t%s\n", node->distance, path);
        dequeueFile(root);
    }
}

void recursiveLevensthein(char *fileInput, char *path, unsigned int distanceLimit){
    queueFile *root = NULL;
    depthSearch(fileInput, path, &root);
    printQueuePath(&root, distanceLimit);
    
}
