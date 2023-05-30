cmake_minimum_required(VERSION 3.0)

project(observateur)

set (SRC observateur.c)
set (HEADERS observateur.h)

add_library(observateur ${SRC} ${HEADERS})
