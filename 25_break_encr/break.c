# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# define ALPHABET_NUM 26

int max_idx (int * array, int n){
  int largest = 0;
  int max_id = -1;
  for (int i=0; i<n ; i++){
    // printf("%d ",array[i]);
    if ( array[i] > largest){
      largest = array[i];
      max_id = i;
    }
  }
  // printf("the largest is %d",largest);
  return max_id;
}
void count_letter (FILE * f, int * array){
  int c;
  while ((c = fgetc(f)) != EOF){
    if (isalpha(c)){
      c = tolower(c)- 'a';
      array[c]+=1;
    }
  }
}
void print_array (int * array, int n){
  for (int i = 0; i<n ; i++){
    printf("%d ",array[i]);
    if ((i+1)%10 == 0){
      printf("\n");
    }
  }
}
int break_cypher(FILE * f){
  int c;
  int n = ALPHABET_NUM;
  int letter_count[ALPHABET_NUM] = {0};
  count_letter (f,letter_count);
  int idx = max_idx(letter_count, n);
  //  print_array(letter_count,n);
  /* if (idx - 4 < 0){
    printf("i could not find a key\n");
    return EXIT_FAILURE;
  }
  printf("%d\n",idx-4);*/
  return idx-4;
}
int main(int argc, char ** argv){
  if (argc != 2){
    fprintf(stderr,"Usage: break input-filename\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL){
    //    printf("could not open the file\n");
    perror("could not open the file");
    return EXIT_FAILURE;
  }
  //  printf("before enter the fun\n");
  if (break_cypher(f)<0){
    printf("i could not find a key\n");
    return EXIT_FAILURE;
  }
  else{
    printf("%d\n",break_cypher(f));
  }
  if (fclose(f) != 0){
    perror("could not close the input file!");
    return EXIT_FAILURE;
  }
  //  printf("after\n");
  return EXIT_SUCCESS;
}
