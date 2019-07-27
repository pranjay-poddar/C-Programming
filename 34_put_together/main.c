#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename,"r");
  if (f == NULL){
    fprintf(stderr,"could not open the file\n");
  }
  counts_t * C_array = createCounts();
  char * buffer = NULL;
  size_t sz=0;
  while(getline(&buffer,&sz,f)>0){
    addCount(C_array, lookupValue(kvPairs,buffer));
  }
  free(buffer);
  if (fclose(f) != 0){
    fprintf(stderr,"could not close the file\n");
  }
  return C_array;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2){
    fprintf(stderr, "Usage: ./programName kv_pairs something_to_count\n");
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i=2; i < argc ; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i],kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    //print the counts from c into the FILE f
    printCounts(c,f);
    //close f
    if (fclose(f) != 0 ){
      fprintf(stderr, "could not close the file\n");
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
