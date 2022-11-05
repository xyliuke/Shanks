cmake_minimum_required(VERSION 3.23)
project(Shanks)
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
#include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
#message("${GTK4_LIBRARY_DIRS}")
#add_definitions(${GTK4_CFLAGS_OTHER})

add_subdirectory(src/widget)

include_directories(./src/)

add_executable(Shanks main.cpp)
target_link_libraries(Shanks widget)