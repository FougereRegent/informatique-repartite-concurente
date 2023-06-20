#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

#include "trace.h"

extern void trace_loop(proc_cons_locker *locker_producteur,
                       proc_cons_locker *locker_consomateur,
                       PipeCommunication *pipes) {

  struct timeval timeout;
  fd_set set;
  Message message_consomateur;
  Message message_observer;

  FD_ZERO(&set);
  FD_SET(pipes->reader.read_descriptor, &set);

  while (1) {
    message_consomateur = consume(locker_consomateur);
    write_into_pipe(&pipes->writer, &message_consomateur, sizeof(Message));

    read_into_pipe(&pipes->reader, &message_observer, sizeof(Message));

    product(locker_producteur, message_observer);
  }
}
