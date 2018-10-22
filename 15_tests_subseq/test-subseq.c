#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int* array, size_t n);
  
int main(void) {
  int array1[] = {1, 2, 3, 4, 5};
  int array2[] = {1, 1, 2, 3, 4};
  int array3[0];
  int array4[] = {-1, 0, -2, 0, 1};
  int array5[] = {-5, -3, -1, 0};
  int array6[] = {-3.12, 1};

  if (maxSeq(array1, 5) != 5) {
    printf("Test failed.");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array2, 5) != 4) {
    printf("Test failed.");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array3, 0) != 0) {
    printf("Test failed.");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array4, 5) != 3) {
    printf("Test failed.");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array5, 4) != 4) {
    printf("Test failed.");
    exit(EXIT_FAILURE);
  }
  if (maxSeq(array6, 2) != 2) {
    printf("Test failed.");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
