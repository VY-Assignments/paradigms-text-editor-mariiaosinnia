cmake_minimum_required(VERSION 3.31)
project(paradigms_text_editor_mariiaosinnia C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(task1
        assignment1/main.c
        assignment1/functions.c
        assignment1/header.h
)

add_executable(task2
        assignment2_oop/main.cpp
        assignment2_oop/TextEditor.cpp
        assignment2_oop/TextEditor.h
)
