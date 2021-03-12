cmake_minimum_required(VERSION 3.17)
project(T2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        T2 src/main.cpp
        src/tinyxml/tinystr.h
        src/tinyxml/tinyxml.h
        src/tinyxml/tinystr.cpp
        src/tinyxml/tinyxml.cpp
        src/tinyxml/tinyxmlerror.cpp
        src/tinyxml/tinyxmlparser.cpp
        src/polygons/Rectangle.cpp
        src/polygons/Rectangle.h
        src/polygons/Circle.cpp
        src/polygons/Circle.h
        src/objects/Player.cpp
        src/objects/Player.h
        src/objects/Arena.cpp
        src/objects/Arena.h
        src/services/Utils.cpp src/services/Utils.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(T2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )