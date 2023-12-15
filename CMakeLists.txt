cmake_minimum_required(VERSION 3.26)
project(C_DSA_GENERIC C)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES 
   "Data Structures/Array/array.c"
   "Data Structures/Array/array.h"
)

add_library(C_DSA_GENERIC STATIC ${SOURCE_FILES})
