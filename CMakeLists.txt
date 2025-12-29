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

add_executable(semantic_3
        Tuan_6/src/charcode.c
        Tuan_6/src/debug.c
        Tuan_6/src/error.c
        Tuan_6/src/main.c
        Tuan_6/src/parser.c
        Tuan_6/src/reader.c
        Tuan_6/src/scanner.c
        Tuan_6/src/symtab.c
        Tuan_6/src/token.c
        Tuan_6/src/semantics.c
)

add_executable(semantic_4
        Tuan_7/Semantic_4/src/charcode.c
        Tuan_7/Semantic_4/src/debug.c
        Tuan_7/Semantic_4/src/error.c
        Tuan_7/Semantic_4/src/main.c
        Tuan_7/Semantic_4/src/parser.c
        Tuan_7/Semantic_4/src/reader.c
        Tuan_7/Semantic_4/src/scanner.c
        Tuan_7/Semantic_4/src/symtab.c
        Tuan_7/Semantic_4/src/token.c
        Tuan_7/Semantic_4/src/semantics.c
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

set_target_properties(semantic_3 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_6"
)

set_target_properties(semantic_4 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_7/Semantic_4"
)

