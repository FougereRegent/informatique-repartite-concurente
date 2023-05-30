cmake_minimum_required(VERSION 3.0)

project(utils)

set (SRC
  convert.c)

set (HEADERS
    convert.h)

add_library(utils ${SRC} ${HEADERS})
target_link_libraries(utils m)
