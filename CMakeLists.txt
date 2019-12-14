cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(3DGraph VERSION 1.0
        DESCRIPTION "Graphics project"
        LANGUAGES CXX)
set(src "3D Graph")
add_library(vec2 ${src}/Vector2D.cpp ${src}/Vector2D.h)
add_library(vec3 ${src}/Vector3D.cpp ${src}/Vector3D.h)
add_library(conloop ${src}/ControlLoop.cpp ${src}/ControlLoop.h)
add_library(camera ${src}/Camera.cpp ${src}/Camera.h)
add_library(renderl ${src}/renderlinux.cpp ${src}/renderlinux.h)

set(SDL2_PATH "/SDL2" CACHE BOOL "" FORCE)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


message(STATUS "sdl2 loc= ${SDL2_PATH} = ${SDL2_INCLUDE_DIRS}")
message(STATUS "lib = ${SDL2_LIBRARY} = ${SDL2MAIN_LIBRARY}")
add_executable(output ${src}/3DGraph.cpp)
target_link_libraries( vec3 vec2)
target_link_libraries(camera vec2 vec3)
target_link_libraries(conloop camera ${SDL2_LIBRARY})
target_link_libraries(renderl ${SDL2_LIBRARY}) 
target_link_libraries(output vec2 vec3 conloop camera renderl ${SDL2_LIBRARY})

