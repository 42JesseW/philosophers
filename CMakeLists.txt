cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

include_directories(philo/includes)

file(GLOB_RECURSE SRCS philo/srcs/*.c)

add_executable(philosophers ${SRCS})

add_subdirectory(tests)
