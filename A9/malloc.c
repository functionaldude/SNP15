/*
 * malloc.cpp
 */


#include "malloc.h"


int sum_allocs = 0;
int sum_frees = 0;
int num_allocated = 0;
int sum_alloc_size = 0;

void allocStats(){
    printf("%d mallocs und %d frees executed\n",sum_allocs,sum_frees);
    printf("allover allocated size: %d byte\n",sum_alloc_size);
    printf("memory areas in use: %d\n",num_allocated);
}

void *malloc(size_t size){
  sum_allocs++;
  sum_alloc_size = sum_alloc_size + size;
  num_allocated++;
  //TODO
    return (void*) 0;
}

void free(void *ptr){
  sum_frees++;
  num_allocated--;
  //TODO
}

void *realloc(void *ptr, size_t size){

	return 0;
}
