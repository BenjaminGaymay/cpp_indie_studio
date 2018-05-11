cmake_minimum_required(VERSION 3.7.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB INCLUDES include/*.hpp)
file(GLOB SRCS srcs/*.cpp)

add_executable(bomberman
            ${INCLUDES}
            ${SRCS})

find_path(IRRLICHT_INCLUDE_DIR irrlicht.h)
include_directories(${IRRLICHT_PATH_INCLUDE})
link_directories(${IRRLICHT_PATH_LIB})
target_link_libraries(bomberman Irrlicht Xxf86vm GL)
