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
        assignment2_oop/Stack.cpp
        assignment2_oop/Stack.h
        assignment2_oop/Cursor.cpp
        assignment2_oop/Cursor.h
        assignment2_oop/Snapshot.cpp
        assignment2_oop/Snapshot.h
)

add_executable(task3
        assignment3_Caesar/dll/caesar.cpp
        assignment3_Caesar/dll/main.cpp
        assignment3_Caesar/static/caesar.h
)

add_executable(task4
        assignment4/main.cpp
        assignment4/TextEditor.cpp
        assignment4/TextEditor.h
        assignment4/Stack.cpp
        assignment4/Stack.h
        assignment4/Cursor.cpp
        assignment4/Cursor.h
        assignment4/Snapshot.cpp
        assignment4/Snapshot.h
        assignment4/Line.h
        assignment4/TextLine.cpp
        assignment4/TextLine.h
        assignment4/ContactLine.cpp
        assignment4/ContactLine.h
        assignment4/CheckListLine.cpp
        assignment4/CheckListLine.h
)
