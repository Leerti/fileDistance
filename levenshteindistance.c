//
//  levenshteindistance.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#include "levenshteindistance.h"


#include <string.h>
#include <stdlib.h>
#include "stackCommand.h"


int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}


int checkNull(int x, int y) {
    if (x == 0) {
        return y;
    } else if (y == 0) {
        return x;
    }
    return 0;
}

int calculateElement(int aboveEl, int leftEl, int diagonalEl, char firstStringChar, char secondStringChar) {
    int cost = 0;
    if (firstStringChar != secondStringChar) {
        cost = 1;
    }
    int el = min(diagonalEl + cost, aboveEl + 1, leftEl + 1);
    return el;
}

int **initMatrix(int **matrix, char *firstString, int x, char *secondString, int y) {
    for (int i = 1; i < x; i++) {
        for (int j = 1; j < y; j++) {
            matrix[i][j] = calculateElement(matrix[i - 1][j], matrix[i][j - 1],
                                            matrix[i - 1][j - 1], firstString[i-1], secondString[j-1]);
        }
    }
    return matrix;
}


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
    return initMatrix(matrix, firstString, x, secondString, y);
}

void deallocateMatrix(int size, int **matrix) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

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

void pushOperation(type_op type, Stack **root, char *firstString, char *secondString, int *x, int *y) {
    if (type == SET) {
        if (firstString[*x - 1] != secondString[*y - 1]) {
            pushNode(root, *y, firstString[*x - 1], SET);
        }
        (*x)--;
        (*y)--;
    } else if (type == DEL) {
        pushNode(root, *y, ' ', DEL);
        (*y)--;
    } else if (type == ADD) {
        pushNode(root, *y, firstString[*x - 1], ADD);
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
                curr[j] = calculateElement(prev[j], curr[j - 1],
                                           prev[j - 1], firstString[i - 1], secondString[j - 1]);

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


Stack *getOperations(char *firstString, char *secondString) {
    int **matrix = createMatrix(firstString, secondString);
    int x = (int) strlen(firstString);
    int y = (int) strlen(secondString);
    Stack *stack = NULL;
    int currentPos = matrix[x][y];
    while (currentPos != 0) {
        pushOperation(defineOperation(matrix, x, y), &stack, firstString, secondString, &x, &y);
        currentPos = matrix[x][y];
    }
    deallocateMatrix(x+ 1, matrix);
    return stack;
}


