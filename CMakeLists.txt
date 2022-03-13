cmake_minimum_required(VERSION 3.13)

set(VERSION_MAJOR 0)            # PROJECT_VERSION_MAJOR
set(VERSION_MINOR 1)            # PROJECT_VERSION_MINOR
set(VERSION_PATCH 0)            # PROJECT_VERSION_PATCH

project(mr_network VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} LANGUAGES CXX)

include_directories(include)
add_executable(mr_network "")
add_subdirectory(src)

find_library(LIBVIFACE viface)
find_library(LIBTINS tins)
find_library(LIBZMQ zmq)


target_link_libraries(mr_network ${LIBVIFACE} ${LIBTINS} ${LIBZMQ})
