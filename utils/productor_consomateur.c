#include <stdio.h>
#include <stdlib.h>

#include "../utils/productor_consomateur.h"
#include "comunication.h"

extern proc_cons_locker *create_lock(Message *buffer, const int size_element) {
  id_sem empty = create_semaphore(size_element);
  id_sem full = create_semaphore(0);
  id_sem mutex = create_mutex();
  proc_cons_locker *locker =
      (proc_cons_locker *)malloc(sizeof(proc_cons_locker));

  locker->empty = empty;
  locker->full = full;
  locker->mutex = mutex;
  locker->size_element = size_element;
  locker->index = 0;
  locker->buffer = buffer;

  return locker;
}

extern void product(proc_cons_locker *locker, Message value) {
  P(locker->empty);
  P(locker->mutex);

  /*Insertion des items*/
  locker->buffer[locker->index] = value;
  locker->index++;

  V(locker->mutex);
  V(locker->full);
}

extern Message consume(proc_cons_locker *locker) {
  Message message;
  P(locker->full);
  P(locker->mutex);

  message = locker->buffer[locker->index];
  locker->index--;

  V(locker->mutex);
  V(locker->empty);
  return message;
}
