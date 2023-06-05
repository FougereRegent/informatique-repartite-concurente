#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include <sys/types.h>
typedef struct {
  pid_t pid;
  int sockfd;
} DataAnnuaire;

extern void initObservateur(const int size);
#endif
