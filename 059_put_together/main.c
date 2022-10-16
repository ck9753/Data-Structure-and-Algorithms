#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * countList = createCounts();

  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;

  FILE * f = fopen(filename, "r");

  while ((len = getline(&line, &sz, f)) >= 0) {
    char * end = strchr(line, '\n');
    size_t length = end - line;

    char * value = malloc((length + 1) * sizeof(*value));
    strncpy(value, line, end - line);
    value[length] = '\0';
    addCount(countList, lookupValue(kvPairs, value));
    free(value);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close file");
  }
  return countList;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Invalid input formats\n");
    exit(EXIT_FAILURE);
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[1], kv);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    if (f != NULL) {
      printCounts(c, f);
    }
    //close f

    //free the memory for outName and c
    free(outName);
    freeCounts(c);

    if (fclose(f) != 0) {
      fprintf(stderr, "Fail to close file\n");
    }
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
