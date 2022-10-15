#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * end = ".counts";
  int len = strlen(inputName) + strlen(end) + 1;
  char * outputName = malloc(len * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, end);
  return outputName;
}
