#include <stdio.h>
#include <stdlib.h>

#include "../utils/productor_consomateur.h"
#include "comunication.h"

extern proc_cons_locker create_lock(Message *buffer, const int size_element) {
  id_sem empty = create_semaphore(size_element);
  id_sem full = create_semaphore(0);
  id_sem mutex = create_mutex();

  proc_cons_locker locker = {.empty = empty,
                             .full = full,
                             .mutex = mutex,
                             .size_element = size_element,
                             .index = 0,
                             .buffer = buffer};
  return locker;
}

extern void product(proc_cons_locker *locker, Message value) {}
extern Message consume(proc_cons_locker *locker) {}
