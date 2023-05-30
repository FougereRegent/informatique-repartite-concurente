#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils/convert.h"

void create_processus(const int);

static pid_t *childs;
static pid_t father;

int main(int argc, char **argv) {
  int nb_processus;

  father = getpid();

  if (argc != 2) {
    printf("Il faut renseigner le nombre de processus esclave");
    exit(1);
  }
  nb_processus = stoi(argv[1]);
  if ((nb_processus = stoi(argv[1])) == -1) {
    printf("L'entrée n'est pas un nombre\n");
    exit(1);
  }

  printf("PID Père : %d\n", father);

  create_processus(nb_processus);

  return EXIT_SUCCESS;
}

void create_processus(const int nb_processus) {
  const unsigned int offset_tab_childs = 1;
  int index;
  childs = (pid_t *)malloc(sizeof(pid_t) * (nb_processus + 1));

  if (childs == NULL) {
    perror("malloc() :");
    exit(1);
  }

  if ((*childs = fork()) == 0) {
    printf("PID Child esclave observer: %d\n", getpid());
    exit(0);
  }

  for (index = 0; index < nb_processus; index++) {
    pid_t currentPid = fork();
    if (currentPid == 0) {
      printf("PID Child esclave : %d\n", getpid());
      exit(0);
    }

    childs[index + offset_tab_childs] = currentPid;
  }
}
