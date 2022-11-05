aux_source_directory(. SRC)
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
message("widget ${GTK4_LIBRARY_DIRS}")
add_definitions(${GTK4_CFLAGS_OTHER})

add_library(widget ${SRC})
target_link_libraries(widget ${GTK4_LIBRARIES})