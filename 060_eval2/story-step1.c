
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;

  //char ** temparr = NULL;
  //size_t tempNum = 0;

  while (getline(&line, &sz, f) >= 0) {
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;
    termRes.eachTermNum = NULL;
    termRes = parseTerm(line);

    termRes = rmUnderScore(termRes, NULL);

    for (size_t i = 0; i < termRes.termNum; i++) {
      printf("%s ", termRes.termarr[i]);
    }
    //free(termRes.termarr);
    //temparr = termRes.termarr;
    //tempNum = termRes.termNum;
  }
  /*
  for (size_t i = 0; i < tempNum; i++) {
    free(temparr[i]);
  }
  */
  //free(temparr);
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
  }
}
