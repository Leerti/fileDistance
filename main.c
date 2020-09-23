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
    
    getCommand("/Users/ale/Desktop/fileIn.rtf", "/Users/ale/Desktop/filemodd.rtf", "/Users/ale/Library/Mobile Documents/com~apple~TextEdit/Documents/fileout.txt");
    
    applyMod("/Users/ale/Desktop/filemodd.rtf", "/Users/ale/Desktop/filemodd.rtf", "/Users/ale/Desktop/fileIn.rtf");
    return 0;
    
}


