#include <stdio.h>
#include <stdlib.h>

#include "intelligence.h"

extern void smart_loop(proc_cons_locker *locker_producteur_client,
                       proc_cons_locker *locker_consomateur_server,
                       proc_cons_locker *locker_consomateur_trace,
                       proc_cons_locker *locker_producteur_trace) {
  Message result_server;
  Message result_trace;

  while (1) {
    result_server = consume(locker_consomateur_server);
    product(locker_producteur_trace, result_server);
  }
}
