cmake_minimum_required(VERSION 3.7.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(bomberman
        include/indie.hpp
        srcs/main.cpp
        srcs/Camera.cpp
        srcs/Core.cpp
        srcs/Irrlicht.cpp)

find_path(IRRLICHT_INCLUDE_DIR irrlicht.h)
include_directories(${IRRLICHT_PATH_INCLUDE})
link_directories(${IRRLICHT_PATH_LIB})
target_link_libraries(bomberman Irrlicht Xxf86vm GL)
