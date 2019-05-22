cmake_minimum_required(VERSION 2.8.7)
project(kattis C CXX)
enable_testing()
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O2 -Wall")

add_executable(sequences
               sequences.cc)

add_executable(10kind
               10kind.cc)

add_executable(2048
               2048.cc)

add_executable(3dprinter
               3dprinter.cc)

add_executable(3sideddice
               3sideddice.cc)

add_executable(4thought
               4thought.cc)

add_executable(a1paper
               a1paper.cc)

add_executable(aaah
               aaah.cc)
