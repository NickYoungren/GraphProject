cmake_minimum_required(VERSION 3.20)
project (GraphProject)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "C:/GraphProject/SFML-2.5.1/lib/cmake/SFML")

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(GraphProject main.cpp TextureManager.cpp Textbox.h Button.h Graphs.h)
target_link_libraries(GraphProject sfml-graphics sfml-window sfml-system)