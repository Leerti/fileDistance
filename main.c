//
//  main.c
//  fileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#include <stdio.h>
#include "levenshteindistance.h"
#include "distance.h"

int main() {
    getDistance("/Users/ale/Desktop/fileIn1.txt","/Users/ale/Desktop/filein2.txt");
    
    getCommand("/Users/ale/Desktop/fileIn1.txt","/Users/ale/Desktop/filein2.txt" ,"/Users/ale/Desktop/fileModt.bin");
    applyMod("/Users/ale/Desktop/filein2.txt", "/Users/ale/Desktop/fileModt.bin", "/Users/ale/Desktop/fileOut.txt");
    
    return 0;
    
}


