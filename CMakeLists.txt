cmake_minimum_required(VERSION 3.7.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

include_directories(SYSTEM lib/irrklang/include)
include_directories(SYSTEM lib/irrlicht/include)
include_directories(include
                    include/GUI
                    include/Events)

add_definitions(
        -g3
        -Wall
        -Wextra)

file(GLOB_RECURSE INCLUDES include/*.hpp)
file(GLOB_RECURSE SRCS_C srcs/Client/*.cpp)
file(GLOB_RECURSE SRCS_SHARED srcs/Shared/*.cpp)
file(GLOB_RECURSE SRCS_S srcs/Server/*.cpp)

add_executable(bomberman
        ${INCLUDES}
        ${SRCS_SHARED}
        ${SRCS_C})

add_executable(server
        ${INCLUDES}
        ${SRCS_S}
        ${SRCS_SHARED})

#[[find_path(IRRLICHT_INCLUDE_DIR irrlicht.h)
include_directories(${IRRLICHT_PATH_INCLUDE})
link_directories(${IRRLICHT_PATH_LIB})
target_link_libraries(bomberman Irrlicht GL pthread)]]



add_library(irrlicht STATIC IMPORTED)
set_property(TARGET irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_HOME_DIRECTORY}/lib/irrlicht/lib/Linux/libIrrlicht.a)
target_link_libraries(bomberman /usr/lib/x86_64-linux-gnu/libX11.so /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1)
target_link_libraries(bomberman irrlicht GL pthread) #IRRLICHT 3D

#[[target_link_libraries(bomberman ${CMAKE_HOME_DIRECTORY}/lib/libIkpFlac.so)
target_link_libraries(bomberman ${CMAKE_HOME_DIRECTORY}/lib/libIkpMP3.so)]]
target_link_libraries(bomberman ${CMAKE_HOME_DIRECTORY}/lib/libIrrKlang.so) #MUSIC IRRKLANG


