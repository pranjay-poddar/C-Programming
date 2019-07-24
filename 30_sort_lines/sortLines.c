#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void print_str_array (char ** array,int size){
  for (int i=0; i< size; i++){
    printf("%s",array[i]);
  }
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  char * line = NULL;
  size_t sz = 0;
  char ** str_array = NULL;
  int n = 0;
  if (argc == 1){
    // read from std input
    while (getline(&line, &sz,stdin) != -1){
      str_array = realloc(str_array,(n+1)*sizeof(*str_array));
      str_array[n] = malloc(sz * sizeof(*str_array[n]));
      strcpy(str_array[n],line);
      n++;
      //      printf("%s\n",line);
    }
    sortData(str_array,n);
    print_str_array(str_array,n);
    free(line);
    // freeing the array
    for (int i=0; i<n; i++){
      free(str_array[i]);
    }
    free(str_array);
  }
  if (argc > 1){
    // read from files
    // open the file
    for (int j=1;j<argc;j++){
      FILE * f = fopen(argv[j],"r");
      if (f == NULL){
	fprintf(stderr,"can not open the file");
	return EXIT_FAILURE;
      }
      while (getline(&line, &sz,f) != -1){
	str_array = realloc(str_array,(n+1)*sizeof(*str_array));
	str_array[n] = malloc(sz * sizeof(*str_array[n]));
	strcpy(str_array[n],line);
	n++;
	// printf("%s\n",line);
      }
      if (fclose(f) != 0){
	fprintf(stderr,"could not close the file!\n");
	return EXIT_FAILURE;
      }
    }
    sortData(str_array,n);
    print_str_array(str_array,n);
    free(line);
    // freeing the array
    for (int i=0; i<n; i++){
      free(str_array[i]);
    }
    free(str_array);
  }
  return EXIT_SUCCESS;
}
