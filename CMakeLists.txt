cmake_minimum_required(VERSION 4.0)
project(SemesterWork C)

set(CMAKE_C_STANDARD 11)

add_executable(SemesterWork main.c
        Includes/header.h
        Includes/header.c
        Includes/strfuncts.h
        Includes/strfuncts.c
        Includes/talking.h
        Includes/talking.c
        Includes/array.h
        Includes/array.c)
