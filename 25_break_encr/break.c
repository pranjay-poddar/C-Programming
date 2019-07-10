# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# define ALPHABET_NUM 26

int max_idx (int * array, int n){
  int largest = 0;
  int max_idx = -1;
  for (int i=0; i<n ; i++){
    if ( array[i] > largest){
      largest = array[i];
      max_idx = i;
    }
  }
  return max_idx;
}
void break_cypher(FILE * f){
  int c;
  int letter_count[ALPHABET_NUM] = {0};
  while(c = fgetc(f) != EOF){
    if (isalpha(c)){
      printf("c is alpha and it is %d\n",c);
      c = tolower(c);
      printf("%d\n",c);
      letter_count[c-97]+=1;
    }
  }
  int idx = max_idx(letter_count, ALPHABET_NUM);
  printf("%d\n",idx-4);
}
int main(int argc, char ** argv){
  if (argc != 2){
    printf("Usage: break input-filename");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL){
    printf("could not open the file\n");
    return EXIT_FAILURE;
  }
  printf("before enter the fun\n");
  break_cypher(f);
  printf("after\n");
  return EXIT_SUCCESS;
}
