#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

#include "../utils/comunication.h"
#include "../utils/productor_consomateur.h"
#include "../utils/wrap_signal.h"
#include "client.h"
#include "init.h"
#include "intelligence.h"
#include "server.h"
#include "trace.h"

#define BUFFER_SIZE 10
#define NB_THREAD 4
#define ERROR -1
#define NO_ERROR 0

static int init_buffer();
static int init_threads();
static void kill_process();
static void *thread_intelligence();
static void *thread_trace();
static void *thread_client();
static void *thread_server();

/*Déclaration des variables static*/
static pthread_t threads[NB_THREAD];
static proc_cons_locker *trace_to_smart;
static proc_cons_locker *smart_to_trace;
static proc_cons_locker *smart_to_client;
static proc_cons_locker *server_to_smart;
static PipeCommunication *pipe_to_observer;
static pid_t *pid;

extern void slave_init(PipeCommunication *pipe) {
  pid = malloc(sizeof(pid));
  *pid = getpid();
  pipe_to_observer = pipe;
  change_signal(SIGTERM, &kill_process);
  /*Init buffer*/
  if (init_buffer() == ERROR) {
    perror("calloc : ");
    exit(EXIT_FAILURE);
  }
  /*Création des 4 threads*/
  if (init_threads() == ERROR) {
    perror("pthread() : ");
    exit(EXIT_FAILURE);
  }

  while (1) {
  }
}

static void kill_process() {
  printf("Kill slave process \n");
  exit(0);
}

static int init_buffer() {
  int error;
  Message *buffer_trace_to_smart =
      (Message *)calloc(BUFFER_SIZE, sizeof(Message));
  Message *buffer_smart_to_trace =
      (Message *)calloc(BUFFER_SIZE, sizeof(Message));
  Message *buffer_smart_to_client =
      (Message *)calloc(BUFFER_SIZE, sizeof(Message));
  Message *buffer_server_to_smart =
      (Message *)calloc(BUFFER_SIZE, sizeof(Message));

  error = buffer_smart_to_trace == NULL || buffer_smart_to_client == NULL ||
                  buffer_trace_to_smart == NULL || buffer_server_to_smart
              ? NO_ERROR
              : ERROR;

  if (error == ERROR)
    return error;

  trace_to_smart = create_lock(buffer_trace_to_smart, BUFFER_SIZE);
  smart_to_trace = create_lock(buffer_smart_to_trace, BUFFER_SIZE);
  smart_to_client = create_lock(buffer_smart_to_client, BUFFER_SIZE);
  server_to_smart = create_lock(buffer_server_to_smart, BUFFER_SIZE);

  return error;
}

static int init_threads() {
  int result = 0;
  result |= pthread_create(&threads[0], NULL, thread_trace, NULL);
  result |= pthread_create(&threads[1], NULL, thread_intelligence, NULL);
  result |= pthread_create(&threads[2], NULL, thread_server, NULL);
  result |= pthread_create(&threads[3], NULL, thread_client, NULL);

  return result != 0 ? ERROR : NO_ERROR;
}

static void *thread_intelligence() {
  smart_loop(smart_to_client, server_to_smart);
  return NULL;
}
static void *thread_trace() {
  trace_loop(trace_to_smart, smart_to_trace, pipe_to_observer);
  return NULL;
}
static void *thread_client() {
  client_loop(smart_to_client);
  return NULL;
}
static void *thread_server() {
  server_loop(server_to_smart, *pid);
  return NULL;
}
