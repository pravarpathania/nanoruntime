cmake_minimum_required(VERSION 3.16)

project(nanoruntime C)

include_directories(include)

add_library(nanoruntime
    src/nanoruntime.c
)

add_executable(hello
    examples/hello.c
)

target_link_libraries(hello nanoruntime)
