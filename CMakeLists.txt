cmake_minimum_required(VERSION 3.23)
project(Shanks)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
link_directories(${GTK4_LIBRARY_DIRS})
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
link_directories(${GTKMM_LIBRARY_DIRS})

add_subdirectory(src/widget)

include_directories(./src/)

add_executable(Shanks main.cpp)
target_link_libraries(Shanks widget)