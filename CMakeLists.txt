cmake_minimum_required(VERSION 3.15)

project(Slinky2D)

add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE SRCS src/*.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRCS}
)


