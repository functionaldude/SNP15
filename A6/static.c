//
//  main.c
//  static_vars
//
//  Created by Zoltán Sasvári on 09.11.14.
//
//
#define ARRAY_SIZE (1024*1024*1024/2)
#define ARRAY_COUNT 2
#include <stdio.h>
#include <unistd.h>

void fill(){
  static char array1[ARRAY_COUNT][ARRAY_SIZE];
  static char array2[ARRAY_COUNT][ARRAY_SIZE];
  printf("array1: 0x%08x, array2: 0x%08x\n", &array1[0][0], &array2[0][0]);
  for (short j = 0; j < ARRAY_COUNT; j++) {
    for (long i = 0; i < ARRAY_SIZE; i++) {
      array1[j][i] = i;
      array2[j][i] = i;
    }
  }
  printf("array1: 0x%08x, array2: 0x%08x\n", &array1[ARRAY_COUNT-1][ARRAY_SIZE-1], &array2[ARRAY_COUNT-1][ARRAY_SIZE-1]);
  sleep(1);
}

int main(int argc, const char * argv[]) {
  printf("Function opened\n");
  fill();
  printf("Function closed\n");
  sleep(2);
  printf("Function opened\n");
  fill();
  printf("Function closed\n");
  sleep(3);
  return 0;
}

