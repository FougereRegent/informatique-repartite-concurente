#ifndef _COMUNICATION_H
#define _COMUNICATION_H

#define DEFAULT_SIZE_BUFFER 1024

typedef enum { LOG, GET_CONF, SET_CONF } TYPE_MESSAGE;

typedef struct {
  TYPE_MESSAGE type;
  char message[DEFAULT_SIZE_BUFFER];
} Message;

#endif
