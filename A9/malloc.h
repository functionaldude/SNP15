/*
 * malloc.h
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>
#include <stdio.h>

typedef size_t mempos;

void *malloc(size_t size);

void free(void *ptr);

void *realloc(void *ptr, size_t size);

void allocStats();


#endif /* MALLOC_H_ */
