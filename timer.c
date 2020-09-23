//
//  timer.c
//  FileDistance
//
//  Created by Alessandra Lerteri Caroletta on 23/09/20.
//

#include "timer.h"
#include <time.h>


time_t start, end;

void start_time(void){
    start = clock();
}

double end_time(void){
    end= clock();
    double execution_time = (double)(end - start) / CLOCKS_PER_SEC;
    return execution_time;
}


