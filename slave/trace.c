#include <stdio.h>
#include <stdlib.h>

#include "trace.h"

extern void trace_loop(proc_cons_locker *locker_producteur,
                       proc_cons_locker *locker_consomateur,
                       PipeCommunication *pipes) {

  Message message_consomateur;
  Message message_observer;

  while (1) {
    message_consomateur = consume(locker_consomateur);
    write_into_pipe(&pipes->writer, &message_consomateur, sizeof(Message));
    read_into_pipe(&pipes->reader, &message_observer, sizeof(Message));

    product(locker_producteur, message_observer);
  }
}
