//
//  levenshteindistance.h
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#ifndef levenshteindistance_h
#define levenshteindistance_h

#include <stdio.h>


#include "stackCommand.h"

int calculateLevenshtein(char *firstString, char *secondString);
Stack *getOperations (char *firstString, char *secondString);




#endif /* levenshteindistance_h */
