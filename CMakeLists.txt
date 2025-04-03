cmake_minimum_required(VERSION 3.22)

project(CSP C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/main.c
                    src/interface.c
                    src/master.c
                    src/sdo.c
                    src/modes/modes.c
                    src/modes/csp.c
                    src/modes/csv.c
                    src/modes/pp.c
                    src/modes/pv.c
                    src/state.c)
target_link_libraries(main /usr/local/lib/libsoem.a)
include_directories(include)
