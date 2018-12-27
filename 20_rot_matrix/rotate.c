void rotate(char matrix[10][10]) {
  char newMat[10][10];
  //  newMat = matrix;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      newMat[i][j] = matrix[j][9 - i];
    }
  }
  return;
}
