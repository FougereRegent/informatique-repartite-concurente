#ifndef _WRAP_PIPE_H
#define _WRAP_PIPE_H

#include <sys/types.h>

typedef struct {
  int read_descriptor;
  int write_descriptor;
} PipeDescriptor;

extern PipeDescriptor *create_pipe(const int nb_pipes);
extern int write_into_pipe(const PipeDescriptor *pipe, const void *message,
                           const size_t size);
extern int read_into_pipe(const PipeDescriptor *pipe, void *message,
                          const size_t size);
#endif
