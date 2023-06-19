#include <stdio.h>
#include <stdlib.h>

#include "intelligence.h"

extern void smart_loop(proc_cons_locker *locker_producteur,
                       proc_cons_locker *locker_consomateur) {
  Message result;

  while (1) {
    result = consume(locker_consomateur);

    printf("consume : %d %s\n", result.type, result.message);
  }
}
