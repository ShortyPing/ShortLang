cmake_minimum_required(VERSION 3.22)
project(SLang C)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY dist)

set(CMAKE_C_STANDARD 99)

add_executable(SLang src/main.c src/const.h src/config.c src/config.h src/f_read.c src/f_read.h src/memory.c src/memory.h src/lifecycle.c src/lifecycle.h)
