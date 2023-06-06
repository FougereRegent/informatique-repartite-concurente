#include <signal.h>
#include <stdlib.h>
#include <sys/signal.h>

#include "wrap_signal.h"

extern int kill_all_process(const pid_t *pids, const int size) {
  const pid_t *index = NULL;
  int result = 0;

  for (index = pids; index < (pids + size); ++index) {
    result |= kill(*index, SIGINT);
  }

  return result != 0 ? -1 : result;
}

extern void change_signal(const int sigid, void (*handler_func)(int)) {
  signal(sigid, handler_func);
}
