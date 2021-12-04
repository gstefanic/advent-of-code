# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(01 C)

add_executable(01 main.c)
target_link_libraries(01 PRIVATE io)
target_link_libraries(01 PRIVATE string_utils)