cmake_minimum_required(VERSION 3.20)
project(CTD C)

set(CMAKE_C_STANDARD 23)

add_executable(tuan1
        Tuan_1/index.c
)
add_executable(scanner
        Tuan_2/incompleted/scanner.c
        Tuan_2/incompleted/reader.c
        Tuan_2/incompleted/token.c
        Tuan_2/incompleted/error.c
        Tuan_2/incompleted/charcode.c)

set_target_properties(tuan1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_1"
)

set_target_properties(scanner PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_2"
)

