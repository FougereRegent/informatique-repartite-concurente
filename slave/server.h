#ifndef _SERVER_H
#define _SERVER_H

#include "../utils/productor_consomateur.h"
#include <sched.h>

extern void server_loop(proc_cons_locker *locker_producteur, pid_t pid);

#endif
