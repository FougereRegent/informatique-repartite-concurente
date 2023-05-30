#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "utils/convert.h"

static void create_processus(const int);

int main(int argc, char **argv) {
  int nb_processus;
  if (argc != 2) {
    printf("Il faut renseigner le nombre de processus esclave");
    exit(1);
  }

  if ((nb_processus = stoi(argv[1])) == -1) {
    printf("L'entrée n'est pas un nombre\n");
    exit(1);
  }

  return EXIT_SUCCESS;
}


static void create_processus(const int nb_processus) {
  
}
