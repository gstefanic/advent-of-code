add_library(
    io
    io.c
    io.h
)

target_include_directories(io PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")