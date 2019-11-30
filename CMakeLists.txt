cmake_minimum_required(VERSION 3.14)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-std=c++14")
set(SOURCE src/)
set(INCLUDE include/)

include_directories(
        ${SOURCE}
        ${INCLUDE})

link_directories(
        ${SOURCE}
        ${INCLUDE})

file(GLOB all
        "${INCLUDE}*.hpp"
        "${SOURCE}*.cpp")

add_executable(${PROJECT_NAME} ${all})

target_link_libraries(${PROJECT_NAME})