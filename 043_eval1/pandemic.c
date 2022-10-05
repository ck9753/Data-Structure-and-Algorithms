#include "pandemic.h"

#include <stdint.h>
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
  unsigned sum_data[3000] = {0};  // why sum_data[n_days]; not working

  for (size_t i = 0; i < n_days - 6; i++) {
    for (size_t j = i; j < n_days + i; j++) {
      sum_data[i] += data[j];
    }
    avg[i] = (double)sum_data[i] / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  unsigned sum_data[3000] = {0};

  for (size_t i = 0; i < n_days; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      sum_data[i] += data[j];
    }
    cum[i] = (double)(sum_data[i] * 100000) / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned max_case = 0;
  //char * country_name;
  char * max_country_name;

  for (size_t i = 0; i < n_countries; i++) {
    //country_name = countries[i].name;
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max_case) {
        max_case = data[i][j];
        max_country_name = countries[i].name;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", max_country_name, max_case);
}
