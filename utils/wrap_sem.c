#include <sys/ipc.h>
#include <sys/sem.h>

#include "wrap_sem.h"

#define MUTEX_COMPTEUR 1

extern id_sem create_semaphore(const int compteur) {
  id_sem id = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
  semctl(id, 0, SETVAL, compteur);
  return id;
}

extern int P(const id_sem id) {
  struct sembuf sem = {.sem_num = 0, .sem_flg = 0, .sem_op = -1};
  return semop(id, &sem, 1);
}

extern int V(const id_sem id) {
  struct sembuf sem = {.sem_num = 0, .sem_flg = 0, .sem_op = 1};
  return semop(id, &sem, 1);
}

extern int create_mutex() {
  id_sem id_mutex = create_semaphore(MUTEX_COMPTEUR);
  return id_mutex;
}

extern int destroy_semaphore(const id_sem id) {
  return semctl(id, 0, IPC_RMID);
}

extern int get_compteur(const id_sem id) { return semctl(id, GETVAL, 0); }

extern int mutex_lock(const id_sem id) { return P(id); }

extern int mutex_unlock(const id_sem id) { return V(id); }
