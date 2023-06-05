#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shared_mem.h"

extern MemoirePartagee superMalloc(const int size) {
#define OFFSET_SIZE_MEM_SHARED 2
  MemoirePartagee memoire;
  memoire.descriptor = shmget(IPC_PRIVATE, size + OFFSET_SIZE_MEM_SHARED,
                              IPC_CREAT | IPC_EXCL | 0600);
  memoire.size = size + OFFSET_SIZE_MEM_SHARED;
  memoire.adresse = (int *)0;
  if (memoire.descriptor != -1)
    memoire.adresse = (int *)shmat(memoire.descriptor, NULL, 0);

  memoire.adresse[0] = memoire.size;
  memoire.adresse[1] = 0; // index du tableau
  return memoire;
}

extern int superFree(MemoirePartagee *m) {
  int retour = shmdt(m->adresse);
  if (retour == -1)
    retour = shmctl(m->descriptor, IPC_RMID, 0);
  return retour;
}

extern void addElement(MemoirePartagee *m, const int value) {
  int *index = m->adresse + 1;
  m->adresse[*index + 2] = value;
  ++*index;
}

extern int *readElements(MemoirePartagee *m) { return m->adresse; }
