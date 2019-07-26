#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname,"r");
  if (f == NULL){
    fprintf(stderr,"could not open the file\n");
    return NULL;
  }
  char * buffer = NULL;
  size_t sz = 0;
  kvarray_t * kv_array = malloc(sizeof(* kv_array));
  kv_array->array = NULL;
  int n = 0 ;
  while (getline(&buffer, &sz,f)>0){
    //    printf("%s",buffer);
    kv_array->array = realloc(kv_array->array,(n+1)* sizeof(*(kv_array->array)));
    char * searchPtr;
    char * keys= malloc(sz*sizeof(*keys));
    char * values = malloc(sz*sizeof(*values));
    if ((searchPtr = strchr(buffer,'='))!=NULL){
      int diff = searchPtr - buffer;
      strcpy(values,searchPtr+1);
      strncpy(keys,buffer,diff);
      keys[diff]='\0';
    }
    else{
      fprintf(stderr,"bad style did not find the equal sign! \n");
    }
    (kv_array->array[n]).key=keys;
    kv_array->array[n].value=values;
    n++;
  }
  free(buffer);
  kv_array->n=n;
  if (fclose(f)!=0){
    fprintf(stderr,"could not close the file\n");
  }
  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int c=0; c<pairs->n;c++){
    free(pairs->array[c].key);
    free(pairs->array[c].value);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i=0; i < pairs->n; i++){
    char * k = pairs->array[i].key;
    char * v = pairs->array[i].value;
    printf("key = '%s' value = '%s'\n",k,v);
  }
}

char * lookupValue(kvarray_t * pairs, const char * Key) {
  //WRITE ME
  // note i changed the key in function protoype to a captial letter 'K'
  // since i used the same word above in the struct 
  for (int j=0; j<pairs->n; j++){
    if (strcmp(pairs->array[j].key,Key)==0){
      return pairs->array[j].value;
    }
  }
  return NULL;
  
}
