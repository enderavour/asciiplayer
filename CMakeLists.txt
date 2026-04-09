cmake_minimum_required(VERSION 3.10)
project(asciiplayer CXX)
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(asciiplayer ${SOURCES})

if (WIN32)
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(asciiplayer ${OpenCV_LIBS})
endif()