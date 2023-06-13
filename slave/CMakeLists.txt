cmake_minimum_required(VERSION 3.0)

project(slave)

set(SRC
    client.c 
    server.c
    trace.c 
    intelligence.c
    init.c
  )

set (HEADERS
    client.h
    server.h 
    trace.h 
    intelligence.h 
    init.h
    )

add_library(slave ${SRC} ${HEADERS})
