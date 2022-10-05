#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  char res_name[64] = {0};
  char res_population[64] = {0};

  const char * ptr1 = line;
  const char * ptr2 = line;
  const char * edptr = line;
  const char * mdptr = line;

  while (*ptr1 != '\0') {
    ptr1 = strchr(ptr1, ',');

    if (ptr1 != NULL) {
      strncpy(res_name, ptr2, ptr1 - ptr2);
      ptr1++;  //point to the first letter of next token
      ptr2 = ptr1;
    }

    else {
      break;
    }
  }

  edptr = strchr(line, '\0');
  mdptr = strchr(line, ',');

  strncpy(res_population, mdptr + 1, edptr - mdptr - 1);

  strcpy(ans.name, res_name);
  ans.population = atoi(res_population);

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  int sum_data[1024] = {0};

  for (int i = 0; i < n_days - 6; i++) {
    for (int j = i; j < n_days + i; j++) {
      sum_data[i] += data[j];
    }
    avg[i] = (double)sum_data[i] / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
