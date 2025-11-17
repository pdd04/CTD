cmake_minimum_required(VERSION 4.0)
project(CTD C)

set(CMAKE_C_STANDARD 23)

add_executable(tuan1
        Tuan_1/index.c
)
set_target_properties(tuan1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Tuan_1"
)