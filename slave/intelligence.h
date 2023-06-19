#ifndef _INTELLIGENCE_H
#define _INTELLIGENCE_H

#include "../utils/productor_consomateur.h"

extern void smart_loop(proc_cons_locker *locker_producteur,
                       proc_cons_locker *locker_consomateur);
#endif
