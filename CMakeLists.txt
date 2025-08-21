cmake_minimum_required(VERSION 3.22)

project(CSP C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/main.c
                    src/interface.c
                    src/master.c
                    src/sdo.c
                    src/modes/modes.c
                    src/modes/csp.c
                    src/state.c
                    src/pdo.c
                    src/dc.c
                    src/registers.c)
target_link_libraries(main soem)
include_directories(include)
