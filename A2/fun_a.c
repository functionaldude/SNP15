#include <stdio.h>
#include <stdlib.h>


struct _sorted_list_ {
  struct _sorted_list_* next;
  struct _sorted_list_* prev;
  int data;  
};

typedef struct _sorted_list_ sorted_list;


sorted_list* sorted_list_create() {
  // TODO: create a new sorted list, 
  // which is used for all the other functions
}

void sorted_list_add(sorted_list** list, int data) {
  // TODO: add the given element to the sorted list,
  // maintain ordering of the elements.
  // Possibly change pointer to first element of list.

  sorted_list * iterator = *list;
  sorted_list * new;

  while (1) {
    if (iterator->next == NULL && iterator->prev == (sorted_list*)0xF0000000) { //erstes
      iterator->data = data;
      iterator->prev = NULL;
      break;
    }
    if (iterator->prev == NULL && data < iterator->data) { //vorne
      new = (sorted_list*)calloc(1, sizeof(sorted_list));
      new->data = data;
      new->prev = NULL;
      new->next = iterator;
      iterator->prev = new;
      *list = new;
      break;
    }
    if (iterator->next != NULL && data >= iterator->data && data < iterator->next->data) { //zwischen
      new = (sorted_list*)calloc(1, sizeof(sorted_list));
      new->data = data;
      new->next = iterator->next;
      new->prev = iterator;
      iterator->next->prev = new;
      iterator->next = new;
      break;
    }
    if (iterator->next == NULL) { //hinten
      new = (sorted_list*)calloc(1, sizeof(sorted_list));
      new->data = data;
      iterator->next = new;
      new->prev = iterator;
      break;
    }
    iterator = iterator->next;
  }
}

void sorted_list_destroy(sorted_list** list) {
  // TODO: destroy the sorted list,
  // free everything so that no memory leak occurs.
  // The pointer to the list has not to be valid
  // after destroying.

  sorted_list * iterator = *list;
  while (iterator->next != NULL) {
    iterator = iterator->next;
  }
  while (iterator->prev != NULL) {
    iterator = iterator->prev;
    free(iterator->next);
  }
  free(iterator);
}

void sorted_list_remove(sorted_list** list, int index) {
  // TODO: remove the element with the given index
  // (index starts with 0), possibly change the pointer
  // to the first element of the list.
  // If the index is not found, do nothing

  sorted_list * iterator = *list;
  unsigned int counter = 0;
  while (counter < index) {
    iterator = iterator->next;
    counter++;
  }
  if (iterator->next != NULL && iterator->prev != NULL) { //zwischen
    iterator->prev->next = iterator->next;
    iterator->next->prev = iterator->prev;
  }
  else if (iterator->prev == NULL) { //erste
    iterator->next->prev = NULL;
    *list = iterator->next;
  }
  else { //letzte
    iterator->prev->next = NULL;
  }
  free(iterator);
}



int main() {
  sorted_list* l = sorted_list_create();
  
  sorted_list_add(&l, 2);
  sorted_list_add(&l, 3);
  sorted_list_add(&l, 4);
  sorted_list_add(&l, 3);
  sorted_list_add(&l, 1);
  sorted_list_remove(&l, 0);
  sorted_list_remove(&l, 1);
  sorted_list_remove(&l, 2);
  
  // expected output: 2 3
  sorted_list* iter = l;
  while(iter != NULL) {
    printf("%d ", iter->data);
    iter = iter->next;
  }
  printf("\n");
  
  sorted_list_destroy(&l);
  
  return 0;
}

