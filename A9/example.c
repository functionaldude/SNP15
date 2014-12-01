/*
 * main.cpp
 */

#include "stdio.h"
#include "malloc.h"


int main(int argc, char** argv){
    int* data[5];
    data[0] = (int*)malloc(5*sizeof(int));
    data[1] = (int*)malloc(20*sizeof(int));
    data[2] = (int*)malloc(40*sizeof(int));
    data[3] = (int*)malloc(100*sizeof(int));
    data[4] = (int*)malloc(500*sizeof(int));

    int i = 0;
    for(i = 0;i<40;i++){
        data[2][i] = 0x99999999;
    }
    for(i = 0;i<500;i++){
        data[4][i] = 666;
    }
    free(data[0]);
    free(data[1]);
    free(data[3]);
    for(i = 0;i<40;i++){
        if(data[2][i] != 0x99999999){
            printf("Error: content changed");
        }
    }
    data[0] = (int*)malloc(25*sizeof(int));
    free(data[0]);
    free(data[2]);
    free(data[4]);
    return 0;
}
