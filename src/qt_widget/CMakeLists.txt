aux_source_directory(. SRC)

set(CMAKE_PREFIX_PATH "/Users/liuke/Applications/Qt/6.3.2/macos")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(qt_widget ${SRC})
target_link_libraries(qt_widget Qt6::Widgets Qt6::Core Qt6::Gui)
