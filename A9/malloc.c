/*
 * malloc.cpp
 */


#include "malloc.h"
#include <unistd.h>

int sum_allocs = 0;
int sum_frees = 0;
int num_allocated = 0;
int sum_alloc_size = 0;
void *base = NULL;

void allocStats(){
    printf("%d mallocs und %d frees executed\n",sum_allocs,sum_frees);
    printf("allover allocated size: %d byte\n",sum_alloc_size);
    printf("memory areas in use: %d\n",num_allocated);
}

void *malloc(size_t size){
  sum_allocs++;
  sum_alloc_size += size;
  num_allocated++;

  block_t current, last;
  size = align_pointer(size);
  if (base) {
    /* First find a block */
    last = base;
    current = find_free_block(&last, size);
    if (current) {
      //there is a fitting free block
      if (BLOCK_SIZE_MIN <= current->size - size){
        // we can split the block
        split_block(current, size);
      }
      current->free=0;
    } else {
        //there are no fitting blocks
        current = new_block(last, size);
      if (!current){ // error
        perror("error at !current");
        return NULL;
      }
    }
  } else {
    //first malloc (base == NULL)
    current = new_block(NULL, size);
    if (!current){
      perror("error at !current");
      return(NULL);
    }
    base = current;
  }
  return current->raw;

}

block_t get_block(void *ptr){
  char* temp = ptr - 20;
  return temp;
}

int valid_address(void *ptr){
  if (base && ptr > base && ptr < sbrk(0)) {
    return (ptr == get_block(ptr)->raw);
  } else {
    return 0;
  }
}

void free(void *ptr){
  sum_frees++;
  num_allocated--;

  block_t current;
  if (valid_address(ptr)){
    current = get_block(ptr);
    current->free = 1;
    if(current->prev && current->prev->free){
      //merge with prev block if works
      current = merge_block(current->prev);
    }
    if (current->next){
      //merge with next
      merge_block(current);
    } else {
      if (current->prev){
        current->prev->next = NULL;
      } else {
        //no more blocks
        base = NULL;
      }
      brk(current);
    }
  } else {
    perror("invalid ptr at free");
  }
}

void copy_block(block_t source, block_t destination) {
  int *data_source = source->raw;
  int *data_destination = destination->raw;
  for (size_t i=0; i*4<source->size && i*4<destination->size; i++){
    data_destination[i] = data_source[i];
  }
}

void *realloc(void *ptr, size_t size){

  if (!ptr) {
    return malloc(size);
  }
  if (valid_address(ptr)) {
    size = align_pointer(size);
    block_t block = get_block(ptr);
    if (size <= block->size && BLOCK_SIZE_MIN <= block->size - size) {
      split_block(block, size);
    } else {
      if (block->next && block->next->free && size <= BLOCK_SIZE + block->size + block->next->size) {
        //merge möglich
        merge_block(block);
        if (BLOCK_SIZE_MIN <= block->size - size) {
          split_block(block, size);
        }
      } else {
        //real malloc
        void *newptr = malloc(size);
        if (!newptr) {
          perror("error at realloc");
          return NULL;
        }
        block_t newblock = get_block(newptr);
        copy_block(block, newblock);
        free(block);
        return newptr;
      }
    }
    return ptr;
  }
	return 0;
}

block_t find_free_block(block_t *last_visited, size_t size){
  block_t current = base;
  while (current && !(current->free && size <= current->size)) { //short-circuit prevents segfault
    *last_visited = current;
    current = current->next;
  }
  return current;
}

block_t new_block(block_t last, size_t size){
  block_t current = sbrk(0);
  if ((int)sbrk(BLOCK_SIZE + size) < -1) {
    //error
    perror("sbrk error");
    return NULL;
  }
  current->size = size;
  current->next = NULL;
  current->prev = last;
  current->free = 0;
  //current->selfptr = 0xAA;
  if (last) {
    last->next = current;
  }
  return current;
}

void split_block(block_t block_old, size_t size){
  block_t block_new = (block_t)(block_old->raw + size); //raw is char -> byte precision calculation
  block_new->size = block_old->size - size - BLOCK_SIZE;
  block_new->free = 1;
  //block_new->selfptr = 0xAA;
  block_new->next = block_old->next;
  block_new->prev = block_old;
  if (block_new->next) {
    block_new->next->prev = block_new;
  }

  block_old->size = size;
  block_old->next = block_new;
}

block_t merge_block(block_t block){
  if (block->next && block->next->free){
    block->size += BLOCK_SIZE + block->next->size;
    block->next = block->next->next;
    if (block->next){
      block->next->prev = block;
    }
  }
  return block;
}