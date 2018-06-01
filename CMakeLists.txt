cmake_minimum_required(VERSION 3.7.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include
                    include/GUI
                    include/Events)

add_definitions(
        -g3
        -Wall
        -Wextra
)

file(GLOB_RECURSE INCLUDES include/*.hpp)
file(GLOB_RECURSE SRCS_C srcs/Client/*.cpp)

file(GLOB_RECURSE SRCS_SHARED srcs/Shared/*.cpp)

add_executable(bomberman
        ${INCLUDES}
        ${SRCS_SHARED}
        ${SRCS_C})

file(GLOB_RECURSE SRCS_S srcs/Server/*.cpp)

find_path(IRRLICHT_INCLUDE_DIR irrlicht.h)
include_directories(${IRRLICHT_PATH_INCLUDE})
link_directories(${IRRLICHT_PATH_LIB})
target_link_libraries(bomberman Irrlicht GL pthread)

include_directories("lib/irrKlang/include")
#[[target_link_libraries(bomberman ${CMAKE_HOME_DIRECTORY}/lib/libIkpFlac.so)
target_link_libraries(bomberman ${CMAKE_HOME_DIRECTORY}/lib/libIkpMP3.so)]]
target_link_libraries(bomberman ${CMAKE_HOME_DIRECTORY}/lib/libIrrKlang.so)

add_executable(server
        ${INCLUDES}
        ${SRCS_S}
        ${SRCS_SHARED})


