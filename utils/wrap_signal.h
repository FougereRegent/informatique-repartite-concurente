#ifndef _WRAP_SIGNAL_H
#define _WRAP_SIGNAL_H
#include <sys/types.h>

extern int kill_all_process(const pid_t *pids, const int size);
extern void change_signal(const int sigid, void (*handler_func)(int));

#endif
