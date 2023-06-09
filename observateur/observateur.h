#ifndef _OBSERVATEUR_H
#define _OBSERVATEUR_H

#include "../utils/shared_mem.h"
#include "../utils/wrap_pipe.h"
#include <sys/types.h>

extern void initObservateur(MemoirePartagee *m, PipeCommunication *pipes,
                            const int size);
#endif
