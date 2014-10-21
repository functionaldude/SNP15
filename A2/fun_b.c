#include <stdio.h>
#include <stdlib.h>

// TODO: insert for_all function here
void for_all(int* array, size_t size, int function(int)){
  int counter = 0;
  for (; counter <= size; counter++) {
    array[counter] = function(array[counter]);
  }
}

// TODO: insert is_any function function here
int is_any(int* array, size_t size, int function(int)){
  int counter = 0;
  for (; counter <= size; counter++) {
    if (function(array[counter])) {
      return 1;
    }
  }
  return 0;
}

int div_3(int x) {
  return x % 3 == 0;
}
int div_5(int x) {
  return x % 5 == 0;
}

int main() {
  int data[] = {1, -2, 3, -4};
  
  // test for all
  for_all(data, sizeof(data) / sizeof(data[0]), abs);
  if(data[0] == 1 && data[1] == 2 && data[2] == 3 && data[3] == 4) {
    printf("for_all test ok\n");
  } else {
    printf("for_all test failed\n");
  }
  
  // test is_any
  if(is_any(data, sizeof(data) / sizeof(data[0]), div_3) &&
     !is_any(data, sizeof(data) / sizeof(data[0]), div_5)) {
    printf("is_any test ok\n");
  } else {
    printf("is_any test failed\n");
  }
  
  return 0;
} 
