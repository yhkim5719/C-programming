size_t maxSeq(int* array, size_t n) {
  int myIt;
  int numSeq = 0;
  int tmpSeq;
  if (array == NULL) {
    return 0;
  } else {
    tmpSeq = 1;
    for (size_t i = 1; i < n+1; i++) {
    myIt = array[i - 1];
    if (myIt < array[i]) {
      tmpSeq++;
    } else {
      if (numSeq < tmpSeq) {
      numSeq = tmpSeq;
      tmpSeq = 1;
      }
    }
  }
  }
  return numSeq;
}
