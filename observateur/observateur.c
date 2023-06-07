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
  pid_t *pids;
  int *size_tab;
  int *index_tab;
  int socket;
} Annuary;

/*Définition des variables globales*/
static Annuary annuary;

/*Définition des prototypes*/
static void kill_process(int code);
static void loop(Annuary annuary);

extern void initObservateur(MemoirePartagee *m) {
  id_sem id_mutex_shared_memory = create_mutex();

  signal(SIGINT, &kill_process);

  mutex_lock(id_mutex_shared_memory);
  annuary.pids = m->adresse + OFFSET_OBSERVER_TAB;
  annuary.size_tab = m->adresse + OFFSET_SIZE;
  annuary.index_tab = m->adresse + OFFSET_INDEX;
  mutex_unlock(id_mutex_shared_memory);

  loop(annuary);
};

static void kill_process(int code) {
  pid_t my_own_pid = getpid();
  int index;
  int size = *annuary.size_tab;

  for (index = 0; index < size; index++) {
    int state;
    waitpid(annuary.pids[index], &state, 0);
  }

  exit(0);
}
static void loop(Annuary annuary) {
  while (1) {
  }
}
