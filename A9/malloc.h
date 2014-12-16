/*
 * malloc.h
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
#include <stdio.h>

#define BLOCK_SIZE 20 //sizeof wont work
#define BLOCK_SIZE_MIN BLOCK_SIZE+16
#define align_pointer(x) (((((x)-1)>>2)<<2)+4)

typedef struct block_s* block_t;

struct block_s {
  size_t size;
  block_t next;
  block_t prev;
  int free;
  char raw[1]; // ghetto method to detect end of metadata block (=start of data)
};

typedef size_t mempos;

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void allocStats();

block_t find_free_block(block_t *last_visited, size_t size);
block_t new_block(block_t last, size_t size);
void split_block(block_t block_old, size_t size);
block_t merge_block(block_t block);

#endif /* MALLOC_H_ */
