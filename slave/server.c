#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../utils/comunication.h"
#include "server.h"

#define PATH_SOCKET "/tmp/socket_"
#define ERROR_SOCKET -1

typedef struct sockaddr_un sockaddr_un;

/*Déclaration des donctions static*/
static int create_socket();

extern void server_loop(proc_cons_locker *locker_producteur, pid_t pid) {}

static int create_socker() {
  int server_socket;
  sockaddr_un server_addr;
  char name_file[32];

  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server_socket == -1) {
    perror("socket() : ");
    return ERROR_SOCKET;
  }

  memset(&server_addr, 0, sizeof(sockaddr_un));
  server_addr.sun_family = AF_UNIX;
  strncpy(name_file, PATH_SOCKET, 32);
  strncat(name_file, "1236", 10);

  return server_socket;
}
