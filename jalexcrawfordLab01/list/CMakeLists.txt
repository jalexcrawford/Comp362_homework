/**
* Name: Alex Crawford
* Lab/task: Lab 1
* Date: 08/29/2022
**/
project(list C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES main.c list.c)

add_executable(list ${SOURCE_FILES})


