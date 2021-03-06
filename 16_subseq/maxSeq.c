#include <stdlib.h>

size_t maxSeq(int* array, size_t n) {
  int myIt;
  int numSeq = 1;
  int tmpSeq;
  if (n == 0) {
    return 0;
  }
  tmpSeq = 1;
  for (size_t i = 1; i < n; i++) {
  myIt = array[i-1];
  if (myIt < array[i]) {
    tmpSeq++;
    if (numSeq < tmpSeq) {
      numSeq = tmpSeq;
    }
  } else {
    tmpSeq = 1;
  }
  }
  return numSeq;
}
  
