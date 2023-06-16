#include <bits/types/struct_timeval.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>

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
static void check_pipe(PipeCommunication *pipe);
static void send_message(PipeCommunication *pipe, Message message);
static void store_log();

extern void initObservateur(MemoirePartagee *m, PipeCommunication *pipes,
                            const int size) {
  int size_tab;
  int index;
  id_sem id_mutex_shared_memory = create_mutex();
  Annuary a;

  signal(SIGTERM, &kill_process);

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

  printf("Fin du process observer\n");
  exit(0);
}
static void loop(Annuary annuary) {
  int index;
  while (1) {
    for (index = 0; index < annuary.size_tab; index++) {
      check_pipe(annuary.node[index].pipe);
    }
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

static void check_pipe(PipeCommunication *pipe) {
  struct timeval timeout;
  fd_set set;

  FD_ZERO(&set);
  FD_SET(pipe->writer.read_descriptor, &set);

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  int retour = select(FD_SETSIZE, &set, NULL, NULL, &timeout);

  if (retour == 0) {
  } else if (retour < 0) {
    perror("select() : ");
  } else {
    Message message;
    int nb_byte = read_into_pipe(&pipe->writer, &message, sizeof(Message));

    printf("%d, %s\n", message.type, message.message);
  }
}

static void send_message(PipeCommunication *pipe, Message message) {}
