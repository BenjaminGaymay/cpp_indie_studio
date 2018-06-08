cmake_minimum_required(VERSION 3.7.2)
project(bomberman)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)


if (APPLE)
    message("Apple not yet supported")
elseif (UNIX)
    message("Linux supported")
    set(STANDARD_UNIX_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 ${STANDARD_UNIX_CXX_FLAGS}")

    file(GLOB_RECURSE INCLUDES ${CMAKE_SOURCE_DIR}/include/*.hpp)
    file(GLOB_RECURSE SRCS_C ${CMAKE_SOURCE_DIR}/srcs/Client/*.cpp)
    file(GLOB_RECURSE SRCS_SHARED ${CMAKE_SOURCE_DIR}/srcs/Shared/*.cpp)
    file(GLOB_RECURSE SRCS_S ${CMAKE_SOURCE_DIR}/srcs/Server/*.cpp)

    add_executable(${PROJECT_NAME}
            ${INCLUDES}
            ${SRCS_SHARED}
            ${SRCS_C})

    add_executable(server
            ${INCLUDES}
            ${SRCS_S}
            ${SRCS_SHARED})


    add_library(irrlicht STATIC IMPORTED)
    set_property(TARGET irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_HOME_DIRECTORY}/lib/irrlicht/lib/Linux/libIrrlicht.a)
    target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libX11.so /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1)
    target_link_libraries(${PROJECT_NAME} irrlicht GL pthread) #IRRLICHT 3D

    target_link_libraries(${PROJECT_NAME} ${CMAKE_HOME_DIRECTORY}/lib/libIkpFlac.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_HOME_DIRECTORY}/lib/libIkpMP3.so)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libIrrKlang.so) #MUSIC IRRKLANG


    include_directories(SYSTEM PRIVATE
            lib/irrklang/include)
    include_directories(SYSTEM PRIVATE
            lib/irrlicht/include)
    include_directories(PUBLIC
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/include/Game
            ${CMAKE_SOURCE_DIR}/include/GUI
            ${CMAKE_SOURCE_DIR}/include/Events
            ${CMAKE_SOURCE_DIR}/include/AI
            ${CMAKE_SOURCE_DIR}/include/Utility
            ${CMAKE_SOURCE_DIR}/include/Local)
elseif (WIN32)
    message("Windows not yet supported")
endif ()