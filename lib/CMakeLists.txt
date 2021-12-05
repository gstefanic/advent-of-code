file(GLOB_RECURSE source_list "*.c" "*.h" "*.cpp" "*.hpp")

add_library(
    lib
    ${source_list}
)

target_include_directories(lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")