#ifndef _TRACE_H
#define _TRACE_H

#include "../utils/productor_consomateur.h"
#include "../utils/wrap_pipe.h"

extern void trace_loop(proc_cons_locker *locker_producteur,
                       proc_cons_locker *locker_consomateur,
                       PipeCommunication *pipes);

#endif
