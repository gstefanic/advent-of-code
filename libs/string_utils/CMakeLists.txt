add_library(
    string_utils
    string_utils.c
    string_utils.h
)

target_include_directories(string_utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")