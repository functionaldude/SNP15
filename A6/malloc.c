//
//  main.c
//  malloc_vars
//
//  Created by Zoltán Sasvári on 09.11.14.
//
//
#define ARRAY_SIZE (2UL*1024*1024*1024)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void fill(){
  char* array1 = malloc(ARRAY_SIZE);
  printf("array1: 0x%08x\n", &array1[0]);
  for (unsigned long i = 0; i < ARRAY_SIZE; i++) {
    array1[i] = i;
  }
  printf("array1: 0x%08x\n", &array1[ARRAY_SIZE-1]);
  perror("array filled");
  sleep(1);
  free(array1);
  perror("array empty");
  sleep(1);
}

int main(int argc, const char * argv[]) {
  perror("Function opened");
  fill();
  perror("Function closed");
  sleep(3);
  perror("Function opened");
  fill();
  printf("Function closed\n");
  sleep(3);
  return 0;
}

