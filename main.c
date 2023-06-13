#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "observateur/observateur.h"
#include "slave/init.h"
#include "utils/convert.h"
#include "utils/shared_mem.h"
#include "utils/wrap_pipe.h"
#include "utils/wrap_sem.h"
#include "utils/wrap_signal.h"

#define SET_NB_PIPES(X) 2 * X

static void create_processus(const int size);
static PipeDescriptor *init_pipes(const int size);
static void stop_app(int code);

static pid_t *childs;
static pid_t father;
static PipeCommunication *communication;

static MemoirePartagee sharedmemory;
int main(int argc, char **argv) {
  int nb_processus;
  int index;
  PipeDescriptor *pipes;
  PipeCommunication *i;

  father = getpid();

  /*Configure shared memory*/

  if (argc != 2) {
    printf("Il faut renseigner le nombre de processus esclave\n");
    exit(1);
  }
  nb_processus = stoi(argv[1]);
  if ((nb_processus = stoi(argv[1])) == -1) {
    printf("L'entrée n'est pas un nombre\n");
    exit(1);
  }

  change_signal(SIGINT, &stop_app);
  pipes = init_pipes(SET_NB_PIPES(nb_processus));

  communication = malloc(sizeof(PipeCommunication) * nb_processus);
  if (communication == NULL) {
    perror("malloc() : ");
    exit(1);
  }

  i = communication;

  for (index = 0; index < SET_NB_PIPES(nb_processus); index++) {
    if (index % 2 == 0) {
      i->reader.write_descriptor = pipes[index].write_descriptor;
      i->reader.read_descriptor = pipes[index].read_descriptor;
    } else {
      i->writer.write_descriptor = pipes[index].write_descriptor;
      i->writer.read_descriptor = pipes[index].read_descriptor;
      i++;
    }
  }
  create_processus(nb_processus);
}

static void create_processus(const int nb_processus) {
#define OFFSET_TAB_CHILDS 1
  int index;
  int stat;
  pid_t pid_observer;
  id_sem id_mutex_proctect_sharedmemory;
  int *state = (int *)malloc(nb_processus * sizeof(int));

  sharedmemory = superMalloc(nb_processus + OFFSET_TAB_CHILDS);

  if (sharedmemory.descriptor == -1) {
    printf("Erreur lors de la création de la mémoire partagée\n");
    exit(1);
  }

  id_mutex_proctect_sharedmemory = create_mutex();

  if (id_mutex_proctect_sharedmemory == -1) {
    printf("Erreur lors de la création du mutex");
    exit(1);
  }

  if (sharedmemory.descriptor == -1) {
    printf("superMalloc(): Erreur d'allocations");
    exit(1);
  }
  if ((pid_observer = fork()) == 0) {
    printf("PID Child esclave observer: %d\n", getpid());
    initObservateur(&sharedmemory, communication, nb_processus);
  }

  mutex_lock(id_mutex_proctect_sharedmemory);
  addElement(&sharedmemory, pid_observer);
  mutex_unlock(id_mutex_proctect_sharedmemory);

  for (index = 0; index < nb_processus; index++) {
    pid_t currentPid = fork();
    if (currentPid == 0) {
      printf("PID Child esclave : %d\n", getpid());
      slave_init(communication);
    }
    mutex_lock(id_mutex_proctect_sharedmemory);
    addElement(&sharedmemory, currentPid);
    mutex_unlock(id_mutex_proctect_sharedmemory);
  }

  waitpid(pid_observer, &stat, 0);
  superFree(&sharedmemory);
}

static void stop_app(int code) {
  int size;
  pid_t *pids = NULL;
  if (sharedmemory.adresse != NULL) {
    kill_all_process(pids, size);
  }

  free(communication);
}

static PipeDescriptor *init_pipes(const int nb_pipes) {
  PipeDescriptor *pipes;
  int index;
  pipes = create_pipe(nb_pipes);
  if (pipes == NULL) {
    perror("malloc() : ");
    exit(1);
  }
  return pipes;
}
