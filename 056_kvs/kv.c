#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * fillPair(const char * line, char delim) {
  const char * x = line;
  const char * y = line;

  x = strchr(x, delim);
  y = strchr(line, '\n');

  if ((x == NULL) || (y == NULL)) {
    fprintf(stderr, "Line does not contain delimiter\n");
    exit(EXIT_FAILURE);
  }

  kvpair_t * newpair = malloc(sizeof(*newpair));

  size_t keyLen = x - line + 1;
  newpair->key = malloc(keyLen * sizeof(*newpair->key));
  strncpy(newpair->key, line, keyLen - 1);
  newpair->key[keyLen - 1] = '\0';

  size_t valLen = y - x;
  newpair->value = malloc(valLen * sizeof(*newpair->value));
  strncpy(newpair->value, x + 1, valLen - 1);
  newpair->key[valLen - 1] = '\0';

  return newpair;
}

void addPair(const char * line, kvarray_t * kvarray) {
  kvpair_t * newpair = NULL;
  newpair = fillPair(line, '=');

  kvarray->kvPairs =
      realloc(kvarray->kvPairs, (kvarray->numPairs + 1) * sizeof(*kvarray->kvPairs));
  kvarray->kvPairs[kvarray->numPairs] = newpair;
  kvarray->numPairs++;

  newpair = NULL;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");

  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    return NULL;
  }

  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->kvPairs = NULL;
  kvarray->numPairs = 0;

  while ((len = getline(&line, &sz, f)) >= 0) {
    addPair(line, kvarray);
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "Close File Error.\n");
    return NULL;
  }

  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numPairs; i++) {
    free(pairs->kvPairs[i]->key);
    free(pairs->kvPairs[i]->value);
    free(pairs->kvPairs[i]);
  }
  free(pairs->kvPairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numPairs; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvPairs[i]->key, pairs->kvPairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numPairs; i++) {
    if (strcmp(pairs->kvPairs[i]->key, key) == 0) {
      return pairs->kvPairs[i]->value;
    }
  }
  return NULL;
}
