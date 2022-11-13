aux_source_directory(. SRC)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

add_library(widget ${SRC})
target_link_libraries(widget ${GTK4_LIBRARIES} ${GTKMM_LIBRARIES})

# copy widget.assets to binary dir
#add_custom_command(TARGET widget
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/widget.assets" "${CMAKE_BINARY_DIR}/widget.assets"
#        VERBATIM
#        )
#add_custom_command(TARGET widget
#        PRE_BUILD
#        COMMAND glib-compile-resources "${CMAKE_CURRENT_SOURCE_DIR}/widget.assets/widget.gresource.xml" "--target=${CMAKE_CURRENT_SOURCE_DIR}/resources.c" --generate-source
#        VERBATIM
#        )