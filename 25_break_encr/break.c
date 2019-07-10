# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# define ALPHABET_NUM 26

int max_idx (int * array, int n){
  int largest = 0;
  int max_id = -1;
  for (int i=0; i<n ; i++){
    printf("%d ",array[i]);
    if ( array[i] > largest){
      largest = array[i];
      max_id = i;
    }
  }
  printf("the largest is %d",largest);
  return max_id;
}
void break_cypher(FILE * f){
  int c;
  int letter_count[ALPHABET_NUM] = {0};
  while((c = fgetc(f)) != EOF){
    //    printf("inside the while%d %c\n",c,c);
    if (isalpha(c)){
      //      printf("c is alpha and it is %d\n",c);
      c = tolower(c);
      //      printf("%d\n",c);
      letter_count[c-97]+=1;
    }
  }
  int n = ALPHABET_NUM;
  int idx = max_idx(letter_count, n);
  printf("%d\n",(idx-4+26)%26);
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
  printf("before enter the fun\n");
  break_cypher(f);
  if (fclose(f) != 0){
    perror("could not close the input file!");
    return EXIT_FAILURE;
  }
  //  printf("after\n");
  return EXIT_SUCCESS;
}
