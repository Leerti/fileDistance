//
//  main.c
//  fileDistance
//
//  Created by Alessandra Lerteri Caroletta on 21/09/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distance.h"

void help() {
    printf("Edit distance: filedistance distance <file1> <file2> \n");
    printf("Generete output instruction: filedistance distance <file1> <file2> <output> \n");
    printf("Apply instruction: filedistance apply <inputfile> <fileMod> <outputfile> \n");
    printf("Search file: filedistance search <inputfile> <dir> \n");
    printf("Search file with limit: filedistance searchall <inputfile> <dir> <limit> \n\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        help();
        exit(1);
    } else if (strcmp(argv[1], "distance") == 0) {
        if (argc == 4) {
            getDistance(argv[2], argv[3]);
        }else if (argc == 5) {
            getCommand(argv[2], argv[3], argv[4]);
        } else perror("Wrong numeber of arguments \n");
    } else if ((strcmp(argv[1], "apply") == 0) && (argc == 5)) {
        applyMod(argv[2], argv[3], argv[4]);
    } else if ((strcmp(argv[1], "search") == 0)) {
        if (argc == 4) search(argv[2], argv[3]);
    } else if (argc == 5) {
            int limit = atoi(argv[4]);
            searchAll(argv[2], argv[3], limit
            );
        
    } else perror("Wrong numeber of arguments \n");
    return 0;
}


