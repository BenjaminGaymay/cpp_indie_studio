cmake_minimum_required(VERSION 3.7.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB INCLUDES include/*.hpp)
file(GLOB SRCS srcs/Client/*.cpp)
file(GLOB SRCS_G srcs/Client/Graphics/*.cpp)
file(GLOB SRCS_O srcs/Client/Objects/*.cpp)

file(GLOB SRCS_SHARED srcs/Shared/*.cpp)

add_executable(bomberman
        ${INCLUDES}
        ${SRCS}
        ${SRCS_G}
        ${SRCS_O}
        ${SRCS_SHARED})

file(GLOB INCLUDES_S include/*.hpp)
file(GLOB SRCS_S srcs/Server/*.cpp)

add_executable(server
        ${INCLUDES_S}
        ${SRCS_S}
        ${SRCS_SHARED})

find_path(IRRLICHT_INCLUDE_DIR irrlicht.h)
include_directories(${IRRLICHT_PATH_INCLUDE})
link_directories(${IRRLICHT_PATH_LIB})
target_link_libraries(bomberman Irrlicht GL)
