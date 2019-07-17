#include <stdio.h>
#include <stdlib.h>
#include "rotate.c"
#define N 10
#define TYPE char
void print_array(TYPE matrix[N][N],int n){
  for (int row=0 ; row < N; row++){
    for (int col=0; col < N; col++){
      printf("%c",matrix[row][col]);
    }
    printf("\n");
  }
}
int main(int argc, char * argv[]){
  FILE * f;
  char matrix[N][N] = {0};
  if (argc > 2){
    fprintf(stderr,"Too many argument\n");
    return EXIT_FAILURE;
  }
  else if(argc < 2){
    printf("one argument expected\n");
    return EXIT_FAILURE;
  }
  else{
    //    char * file_name[]=argv[1];
    //    printf("%s\n",argv[1]);
    if ((f = fopen(argv[1],"r")) == NULL){
      printf("could not open the file\n");
      return EXIT_FAILURE;
    }
  }
  int c;
  for (int i=0; i < N ; i++){//rows
    for (int j=0 ; j < N; j++){//columns
      //      printf("%c",c);
      if ((c = fgetc(f)) == EOF){
	printf("wrong format: EOF at the middle of the data\n");
	return EXIT_FAILURE;
      }
      else if (c == '\n'){
	printf("wrong format: early newline\n");
	return EXIT_FAILURE;
      }
      else{
	matrix[i][j] = c;
      }
    }
    if (fgetc(f) != '\n'){
      printf("wrong format: no newline after 10 char\n");
      return EXIT_FAILURE;
    }
  }
  rotate(matrix);
  print_array(matrix,N);
  return EXIT_SUCCESS;
}
