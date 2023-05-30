cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_COMPILER gcc)

project(TP)

add_subdirectory(slave)
add_subdirectory(utils)
add_subdirectory(observateur)

add_executable(bin main.c)

target_link_libraries(bin slave utils observateur)
