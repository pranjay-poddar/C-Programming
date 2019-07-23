#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outName = malloc((strlen(inputName)+8) * sizeof(* outName));
  strcpy(outName,inputName);
  strcat(outName,".counts");
  return outName;
}
