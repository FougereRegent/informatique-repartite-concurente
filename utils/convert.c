#include <math.h>
#include <string.h>

#include "convert.h"

#define ZEROCHAR '0'
#define NINECHAR '9'

extern int stoi(const char *chaine) {
  unsigned int size_chaine = strlen(chaine);
  unsigned int exp = size_chaine - 1;
  unsigned int index;
  int result;

  for (index = 0; index < size_chaine; ++index) {
    char c = chaine[index];
    if (c < ZEROCHAR || c > NINECHAR) {
      return -1;
    }

    int n = c - ZEROCHAR;

    result += n * pow(10, exp--);
  }
  return result;
}
