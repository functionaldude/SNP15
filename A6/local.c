//
//  main.c
//  local_vars
//
//  Created by Zoltán Sasvári on 09.11.14.
//
//
#define ARRAY_SIZE 8374505
#include <stdio.h>
#include <unistd.h>

void fill(){
  char array1[ARRAY_SIZE];
  printf("array1: 0x%08x\n", &array1[0]);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    array1[i] = i;
  }
  printf("array1: 0x%08x\n", &array1[ARRAY_SIZE-1]);
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
