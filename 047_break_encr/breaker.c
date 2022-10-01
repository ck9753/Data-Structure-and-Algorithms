#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int max_index(int * array) {
  int index = 0;
  int max = array[0];

  for (int i = 0; i < 25; i++) {
    if (array[i + 1] > max) {
      max = array[i + 1];
      index = i + 1;
    }
  }
  return index;
}

void key_exe(FILE * f) {
  int c;
  int letter[26];  // the number of alphabet
  for (int i = 0; i < 26; i++) {
    letter[i] = 0;
  }

  while ((c = fgetc(f)) != EOF) {
    if ((isalpha(c))) {
      c = tolower(c);
      letter[c - 'a']++;
    }
  }

  int max = max_index(letter);
  int key;

  if (max >= 4) {
    key = max - 4;
  }
  else {
    key = max + 26 - 4;
  }

  printf("%d\n", key);
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[2], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  key_exe(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
