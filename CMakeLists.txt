cmake_minimum_required(VERSION 3.3)
project(ecelecar C)

set(CMAKE_C_STANDARD 23)

add_executable(ecelecar main.c header.h sous-fonctions.c)
