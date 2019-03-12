cmake_minimum_required(VERSION 2.8)
project(fasttext-server)

# The version number.
set (fasttext-server_VERSION_MAJOR 0)
set (fasttext-server_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${CMAKE_SOURCE_DIR}/include")
find_library(http-parser-shared NAMES libhttp_parser.so PATHS /usr/lib /usr/local/lib)
find_library(fasttext-shared NAMES libfasttext.so PATHS /usr/lib /usr/local/lib)
find_library(uv-shared NAMES libuv.so PATHS /usr/lib /usr/local/lib)

add_subdirectory(src)