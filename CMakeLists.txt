cmake_minimum_required(VERSION 3.7.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include
                    ./include/GUI
                    ./include/Events)

add_definitions(
        -Wall
        -Wextra
)

file(GLOB INCLUDES include/*.hpp)
file(GLOB_RECURSE SRCS_C srcs/Client/*.cpp)

file(GLOB_RECURSE SRCS_SHARED srcs/Shared/*.cpp)

add_executable(bomberman
        ${INCLUDES}
        ${SRCS_SHARED}
        ${SRCS_C})

file(GLOB_RECURSE SRCS_S srcs/Server/*.cpp)

add_executable(server
        ${INCLUDES}
        ${SRCS_S}
        ${SRCS_SHARED})


find_path(IRRLICHT_INCLUDE_DIR irrlicht.h)
include_directories(${IRRLICHT_PATH_INCLUDE})
link_directories(${IRRLICHT_PATH_LIB})
target_link_libraries(bomberman Irrlicht GL pthread)