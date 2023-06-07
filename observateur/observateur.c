#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/unistd.h>

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

/*Définition des prototypes*/
static void kill_process(const int code);
static void loop(Annuary annuary);

extern void initObservateur(MemoirePartagee *m) {
  Annuary annuary = {.pids = m->adresse + OFFSET_OBSERVER_TAB,
                     .size_tab = m->adresse + OFFSET_SIZE,
                     .index_tab = m->adresse + OFFSET_INDEX};

  loop(annuary);
}

static void kill_procrss(const int code) { pid_t my_own_pid = getpid(); }
static void loop(Annuary annuary) {
  while (1) {
  }
}
