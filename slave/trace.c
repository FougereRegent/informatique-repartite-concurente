#include <stdio.h>
#include <stdlib.h>

#include "trace.h"

extern void trace_loop(proc_cons_locker *locker_producteur,
                       proc_cons_locker *locker_consomateur,
                       PipeCommunication *pipes) {

  Message message_consomateur;

  while (1) {
    message_consomateur = consume(locker_consomateur);
  }
}
