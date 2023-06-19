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
#define ERROR_BIND -2
#define ERROR_LISTEN -3

typedef struct sockaddr_un sockaddr_un;

/*Déclaration des donctions static*/
static int create_socket(pid_t pid);

extern void server_loop(proc_cons_locker *locker_producteur, pid_t pid) {
  int socket_client;
  sockaddr_un client_addr;
  int ret;

  ret = create_socket(pid);
  if (ret < 0)
    exit(EXIT_FAILURE);

  printf("Création du socket %d\n", pid);
}

static int create_socket(pid_t pid) {
#define SIZE_NAME_FILE 64
#define SIZE_PID_STRING 21
  int server_socket;
  sockaddr_un server_addr;
  char name_file[SIZE_NAME_FILE];
  char pid_string[SIZE_PID_STRING];

  server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

  if (server_socket == -1) {
    perror("socket() : ");
    return ERROR_SOCKET;
  }

  snprintf(pid_string, SIZE_PID_STRING, "%d", pid);
  strncpy(name_file, PATH_SOCKET, SIZE_NAME_FILE);
  strncat(name_file, pid_string, SIZE_PID_STRING);

  memset(&server_addr, 0, sizeof(sockaddr_un));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, name_file, sizeof(server_addr.sun_path));

  printf("Socket : %s\n", server_addr.sun_path);

  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(sockaddr_un)) == -1) {
    perror("bind() : ");
    return ERROR_BIND;
  }

  if (listen(server_socket, 5) == -1) {
    perror("listen() : ");
    return ERROR_LISTEN;
  }

  return server_socket;
}
