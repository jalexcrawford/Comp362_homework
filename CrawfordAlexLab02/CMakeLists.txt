#[[/**
* Name: Alex Crawford
* Lab/task: Lab 2
* Date: 09/4/2022
**/]]
project(list C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES sub.c)

add_executable(sub ${SOURCE_FILES})

