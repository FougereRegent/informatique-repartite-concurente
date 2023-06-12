#include "wrap_pipe.h"
#include <stdlib.h>
#include <unistd.h>

extern PipeDescriptor *create_pipe(const int nb_pipes) {
  int index;
  PipeDescriptor *pipes =
      (PipeDescriptor *)malloc(sizeof(PipeDescriptor) * nb_pipes);

  for (index = 0; index < nb_pipes; index++) {
    int tubes[2];
    if (pipe(tubes) != 0)
      break;

    pipes[index].read_descriptor = tubes[0];
    pipes[index].write_descriptor = tubes[1];
  }
  return pipes;
}

extern int write_into_pipe(const PipeDescriptor *pipe, const void *message,
                           const size_t size) {
  int write_descriptor = pipe->write_descriptor;
  int writed_size;

  writed_size = write(write_descriptor, message, size);
  return writed_size;
}

extern int read_into_pipe(const PipeDescriptor *pipe, void *message,
                          const size_t size) {
  int read_descriptor = pipe->read_descriptor;
  int read_size;

  read_size = read(read_descriptor, message, size);
  return read_size;
}
