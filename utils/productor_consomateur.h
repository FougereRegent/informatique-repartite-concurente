#ifndef _PRODUCTOR_H
#define _PRODUCTOR_H

#include "../utils/wrap_sem.h"
#include "comunication.h"

typedef struct {
  id_sem empty;
  id_sem full;
  id_sem mutex;
  int size_element;
  int index;
  Message *buffer;
} proc_cons_locker;

extern proc_cons_locker create_lock(Message *buffer, const int size_element);
extern void product(proc_cons_locker *locker, Message value);
extern Message consume(proc_cons_locker *locker);
#endif
