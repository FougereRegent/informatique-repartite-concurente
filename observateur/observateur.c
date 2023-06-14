#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>

#include "../utils/wrap_sem.h"
#include "../utils/wrap_signal.h"
#include "observateur.h"

#define OFFSET_OBSERVER_TAB 3
#define OFFSET_INDEX 1
#define OFFSET_SIZE 0

/*Défintion des structures*/
typedef struct {
  pid_t pid;
  int socket;
  PipeCommunication *pipe;
} nodeAnnuary;

typedef struct {
  nodeAnnuary *node;
  int size_tab;
} Annuary;

static Annuary *annuary;

/*Définition des prototypes*/
static void kill_process(int code);
static void loop(Annuary annuary);
static Annuary create_annuary(const pid_t *pids, PipeCommunication *pipes,
                              const int size);

extern void initObservateur(MemoirePartagee *m, PipeCommunication *pipes,
                            const int size) {
  int size_tab;
  int index;
  id_sem id_mutex_shared_memory = create_mutex();
  Annuary a;

  signal(SIGINT, &kill_process);

  mutex_lock(id_mutex_shared_memory);
  size_tab = *(m->adresse + OFFSET_SIZE);
  mutex_unlock(id_mutex_shared_memory);

  for (index = 0; index < size; index++) {
  }

  while (size_tab != size) {
    mutex_lock(id_mutex_shared_memory);
    size_tab = *(m->adresse + OFFSET_INDEX) - 1;
    mutex_unlock(id_mutex_shared_memory);
  }

  a = create_annuary(m->adresse + OFFSET_OBSERVER_TAB, pipes, size);

  for (index = 0; index < size; index++) {
    printf("PID : %d\n", a.node[index].pid);
    printf("Reader %d : %d | %d\n", index,
           a.node[index].pipe->reader.read_descriptor,
           a.node[index].pipe->reader.write_descriptor);
    printf("Writer %d : %d | %d\n", index,
           a.node[index].pipe->writer.read_descriptor,
           a.node[index].pipe->writer.write_descriptor);
  }

  annuary = &a;
  loop(a);
};

static void kill_process(int code) {
  pid_t my_own_pid = getpid();
  int index;
  int size = annuary->size_tab;

  for (index = 0; index < size; index++) {
    int state;
    waitpid(annuary->node[index].pid, &state, 0);
  }

  exit(0);
}
static void loop(Annuary annuary) {
  while (1) {
  }
}

static Annuary create_annuary(const pid_t *pids, PipeCommunication *pipes,
                              const int size) {
  int index;
  Annuary annuary;
  annuary.node = (nodeAnnuary *)malloc(sizeof(nodeAnnuary) * size);
  annuary.size_tab = size;

  for (index = 0; index < size; index++) {
    nodeAnnuary node = {.pid = pids[index], .pipe = (pipes + index)};
    annuary.node[index] = node;
  }
  return annuary;
}

static void check_pipe() {}
