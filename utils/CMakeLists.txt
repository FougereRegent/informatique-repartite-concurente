cmake_minimum_required(VERSION 3.0)

project(utils)

set (SRC
  convert.c
  shared_mem.c
  wrap_sem.c
  wrap_signal.c
  wrap_pipe.c
  productor_consomateur.c)

set (HEADERS
    convert.h
    shared_mem.h
    wrap_sem.h
    wrap_signal.h
    wrap_pipe.h
    comunication.h
    productor_consomateur.h)

add_library(utils ${SRC} ${HEADERS})
target_link_libraries(utils m)
