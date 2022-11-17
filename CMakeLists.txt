cmake_minimum_required(VERSION 3.15)

project(Slinky2D
        VERSION 0.1.0
        DESCRIPTION "2D Physics Engine in C++"
        )

set(CMAKE_CXX_STANDARD 17)

# google test

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# library

add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE SRCS src/*.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRCS}
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

# SFML

add_subdirectory(3rdparty/sfml)

# examples

add_executable(Test examples/test/main.cpp)
target_link_libraries(Test
        PRIVATE
        ${PROJECT_NAME} sfml-system sfml-graphics sfml-window)

add_executable(BoundingTest examples/FallingBox/main.cpp)
target_link_libraries(BoundingTest
        PRIVATE
        ${PROJECT_NAME} sfml-system sfml-graphics sfml-window)

# tests
include(GoogleTest)

enable_testing()

add_executable(AABBTest tests/AABBTest.cpp)
target_link_libraries(
        AABBTest
        GTest::gtest_main
        ${PROJECT_NAME}
)

gtest_discover_tests(AABBTest)