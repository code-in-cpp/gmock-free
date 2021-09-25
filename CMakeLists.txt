cmake_minimum_required(VERSION 3.19)
project(gmock_free)

set(CMAKE_CXX_STANDARD 11)

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
add_executable(gmock_free test/gmock-free-test.cpp)
target_link_libraries(gmock_free
    PRIVATE
    gtest
    gmock
    gmock_main)

target_include_directories(gmock_free
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)