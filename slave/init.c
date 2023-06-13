#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>

#include "../utils/wrap_signal.h"
#include "init.h"

static void kill_process();

extern void slave_init(PipeDescriptor *pipe) {

  change_signal(SIGINT, &kill_process);
  while (1) {
  }
}

static void kill_process() {
  printf("Kill slave process \n");
  exit(0);
}
