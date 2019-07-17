void rotate(char matrix [10][10]){
  int dum_arr [10][10];
  for (int i=0; i<10; i++){
    for (int j=0; j<10; j++){
      dum_arr[j][9-i]= matrix[i][j];
    }
  }
  for (int ii = 0 ; ii < 10 ; ii++){
    for (int jj = 0 ; jj < 10 ; jj++){
      matrix[ii][jj] = dum_arr[ii][jj];
    }
  }
}
