#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

#include "../utils/wrap_signal.h"
#include "init.h"

#define BUFFER_SIZE 10

static void kill_process();
static void thread_intelligence();
static void thread_trace();
static void thread_client();
static void thread_server();

extern void slave_init(PipeCommunication *pipe) {
  change_signal(SIGTERM, &kill_process);

  /*Création des 4 threads*/
}

static void kill_process() {
  printf("Kill slave process \n");
  exit(0);
}

static void thread_intelligence() {}
static void thread_trace() {}
static void thread_client() {}
static void thread_server() {}
