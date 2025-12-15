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

add_executable(parser
        Tuan_3/src/charcode.c
        Tuan_3/src/error.c
        Tuan_3/src/main.c
        Tuan_3/src/parser.c
        Tuan_3/src/reader.c
        Tuan_3/src/scanner.c
        Tuan_3/src/token.c
)

add_executable(symtab
        Tuan_4/debug.c
        Tuan_4/main.c
        Tuan_4/symtab.c
)

add_executable(semantic_2
        Tuan_5/src/charcode.c
        Tuan_5/src/debug.c
        Tuan_5/src/error.c
        Tuan_5/src/main.c
        Tuan_5/src/parser.c
        Tuan_5/src/reader.c
        Tuan_5/src/scanner.c
        Tuan_5/src/symtab.c
        Tuan_5/src/scanner.c
        Tuan_5/src/token.c
)

set_target_properties(tuan1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_1"
)

set_target_properties(scanner PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_2"
)

set_target_properties(parser PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_3"
)

set_target_properties(symtab PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_4"
)

set_target_properties(semantic_2 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_5"
)

