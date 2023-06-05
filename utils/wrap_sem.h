#ifndef _WRAP_SEM_H
#define _WRAP_SEM_H

typedef int id_sem;
typedef struct {
  int id;
  int P;
  int V;
} Semaphore;

extern int create_semaphore(const int compteur);
extern int P(const id_sem id);
extern int V(const id_sem id);

extern int create_mutex();
extern int mutex_lock(const id_sem id);
extern int mutex_unlock(const id_sem id);

extern int destroy_semaphore(const id_sem id);

#endif
