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
    Message message = {.size = 1024, SET_CONF, "salut tous le monde"};
    int size = write_into_pipe(&pipe->writer, &message, sizeof(Message));

    printf("Taille : %d, descriptor : %d\n", size,
           pipe->writer.write_descriptor);

    sleep(100);
  }
}

static void kill_process() {
  printf("Kill slave process \n");
  exit(0);
}
