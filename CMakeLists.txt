cmake_minimum_required(VERSION 3.17)
project(T3)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(
        T3 src/main.cpp
        src/tinyxml/tinystr.h
        src/tinyxml/tinyxml.h
        src/tinyxml/tinystr.cpp
        src/tinyxml/tinyxml.cpp
        src/tinyxml/tinyxmlerror.cpp
        src/tinyxml/tinyxmlparser.cpp
        src/objects/Arena.cpp
        src/objects/Arena.h
        src/services/Utils.cpp src/services/Utils.h src/input/Mouse.cpp src/input/Mouse.h src/model/Image.cpp src/model/Image.h src/model/AutoArray.cpp src/model/AutoArray.h src/model/Model.cpp src/model/Model.h src/objects/ModelPlayer.cpp src/objects/ModelPlayer.h src/objects/Camera.cpp src/objects/Camera.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(T3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )