
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // check if command include correct number of inputs
  if (argc != 2) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  // check if the file open properly
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // initialize line and size
  char * line = NULL;
  size_t sz = 0;

  // read and get each line
  while (getline(&line, &sz, f) >= 0) {
    //declare and initialize term result for the function parseTerm
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;
    termRes = parseTerm(line);

    // declare and initizliae second term result for the function rmUnderscore
    termInfo_t termRes2;
    termRes2.termarr = NULL;
    termRes2.termNum = 0;
    termRes2 = rmUnderScore(termRes, NULL);

    freeTermInfo(termRes);
    // print the Term with cat
    printTermInfo(termRes2);
    freeTermInfo(termRes2);
  }
  free(line);

  // check if the file was closed
  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
  }
}
