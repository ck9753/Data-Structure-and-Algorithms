
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // check if the the program get correct command
  if (argc != 2) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  // check if the file is opened
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    // termInfo_t struct to parse each term
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;
    termRes.space = NULL;
    termRes = parseTerm(line);

    // termInfo_to struct to convert categories to "cat"
    termInfo_t termRes2;
    termRes2.termarr = NULL;
    termRes2.termNum = 0;
    termRes2.space = NULL;
    termRes2 = cdCatToWord(termRes, NULL);

    freeTermInfo(termRes);

    // print parsed terms
    printTermInfo(termRes2);

    freeTermInfo(termRes2);
  }
  free(line);

  // check if the file is closed
  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
    exit(EXIT_FAILURE);
  }
}
