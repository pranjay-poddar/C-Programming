#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

#define MAX_LINE_LENGTH 500

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * count = malloc (sizeof(*count));
  count->n=0;
  count->unknown=0;
  count->count_array=NULL;
  return count;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //  printf("%s\n",name);
  int found = 0;
  if (name == NULL){
    c->unknown+=1;
  }
  else{
    for (int i =0; i < c->n; i++){
      if (strcmp(c->count_array[i].keyString, name)==0){
	c->count_array[i].repeat+=1;
	found =1;
	break;
      }
    }
    if (found == 0){
      c->count_array = realloc(c->count_array, (c->n+1)*sizeof(*(c->count_array)));
      //try to malloc this
      c->count_array[c->n].keyString = malloc(MAX_LINE_LENGTH*sizeof(char));
      strcpy(c->count_array[c->n].keyString , name);
      c->count_array[c->n].repeat = 1;
      c->n +=1;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int j=0; j< c->n;j++){
    fprintf(outFile,"%s: %d\n",c->count_array[j].keyString,c->count_array[j].repeat);
  }
  if (c->unknown !=0){
    fprintf(outFile,"<unknown> : %d\n",c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int k=0;k < c->n ; k++){
    free(c->count_array[k].keyString);
  }
  free(c->count_array);
  free(c);
}
