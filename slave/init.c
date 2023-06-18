#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

#include "../utils/comunication.h"
#include "../utils/wrap_signal.h"
#include "init.h"

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
static Message *buffer_trace_to_smart;
static Message *buffer_smart_to_trace;
static Message *buffer_smart_to_client;
static Message *buffer_server_to_smart;

extern void slave_init(PipeCommunication *pipe) {
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
}

static void kill_process() {
  printf("Kill slave process \n");
  exit(0);
}

static int init_buffer() {
  buffer_trace_to_smart = (Message *)calloc(BUFFER_SIZE, sizeof(Message));
  buffer_smart_to_trace = (Message *)calloc(BUFFER_SIZE, sizeof(Message));
  buffer_smart_to_client = (Message *)calloc(BUFFER_SIZE, sizeof(Message));
  buffer_server_to_smart = (Message *)calloc(BUFFER_SIZE, sizeof(Message));

  return buffer_smart_to_trace == NULL || buffer_smart_to_client == NULL ||
                 buffer_trace_to_smart == NULL || buffer_server_to_smart
             ? NO_ERROR
             : ERROR;
}

static int init_threads() {
  int result = 0;
  result |= pthread_create(&threads[0], NULL, thread_trace, NULL);
  result |= pthread_create(&threads[1], NULL, thread_intelligence, NULL);
  result |= pthread_create(&threads[2], NULL, thread_server, NULL);
  result |= pthread_create(&threads[3], NULL, thread_client, NULL);

  return result != 0 ? ERROR : NO_ERROR;
}

static void *thread_intelligence() { return NULL; }
static void *thread_trace() { return NULL; }
static void *thread_client() { return NULL; }
static void *thread_server() { return NULL; }
