#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

#include "../utils/wrap_signal.h"
#include "init.h"

static void kill_process();
static void create_thread();

extern void slave_init(PipeCommunication *pipe) {

  change_signal(SIGTERM, &kill_process);
  while (1) {
    int size = write_into_pipe(&pipe->writer, "test", strlen("test"));
    printf("Taille : %d, descriptor : %d\n", size,
           pipe->writer.write_descriptor);

    sleep(10);
  }
}

static void kill_process() {
  printf("Kill slave process \n");
  exit(0);
}
