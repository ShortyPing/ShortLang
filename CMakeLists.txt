cmake_minimum_required(VERSION 3.22)
project(SLang C)

set(CMAKE_C_STANDARD 99)

add_executable(SLang main.c const.h config.c config.h f_read.c f_read.h)
