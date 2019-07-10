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
      c = tolower(c);
      letter_count[c-'a']+=1;
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
  break_cypher(f);
  return EXIT_SUCCESS;
}
